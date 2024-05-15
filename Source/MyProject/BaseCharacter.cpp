// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BaseBarrel.h"
#include "HealthComp.h"
#include "RivetAbilitySystemComponent.h"
#include "RivetAttributeSet.h"
#include "RivetData.h"
#include "RivetGameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("Character Comp"));
	AbilitySystemComponent = CreateDefaultSubobject<URivetAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<URivetAttributeSet>(TEXT("Attributes"));
	
}

// Called when the game starts or when spawned	
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();	
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	AddStartupGameplayAbilities();
	
}

void ABaseCharacter::MoveForward(float Value)
{
	// prevents nullptr
	if (Controller == nullptr or Value == 0.0f)
	{
		return;
	}

	// find out which direction is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
		
	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value * MovementSpeed);
	
}

void ABaseCharacter::MoveSides(float Value)
{
	// prevents nullptr
	if (Controller == nullptr or Value == 0.0f)
	{
		return; 
	}
	
	// find out which direction is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
		
	// get right vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
	// add movement in that direction
	AddMovementInput(Direction, Value * MovementSpeed);
	
}


URivetAttributeSet* ABaseCharacter::GetAttributeSet() const
{
	return Attributes;
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                 AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Display, TEXT("I have been hit %s"), *GetName());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), bIsParried ? TEXT("parried"): TEXT("not parried"));
	
	if(EventInstigator && EventInstigator->GetCharacter() == this )
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actor is trying to damage itself"));
		
		return 0;
		
	}
	
	if(HealthComp->TakeDamage(Damage)) // Checks if we are dead
	{
		//SetActorEnableCollision(false);
		//SetActorHiddenInGame(true);
	}

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser) + Damage;
}

FActiveGameplayEffectHandle ABaseCharacter::AddPassiveEffect(const TSubclassOf<UGameplayEffect>& Effect)
{
	UE_LOG(LogTemp, Warning, TEXT("I have been called"))
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle GameplayEffectSpecHandle =
		AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContextHandle);

	if(GameplayEffectSpecHandle.IsValid())
	{
		const FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), AbilitySystemComponent );
		return ActiveGameplayEffectHandle;
	}
	return NULL;
}

void ABaseCharacter::AddActiveAbility(const TSubclassOf<URivetGameplayAbility>& Ability) 
{
	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
	Ability, 1,static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
}

void ABaseCharacter::RemoveActiveAbility()
{
	//AbilitySystemComponent->RemoveActiveEffects()
}

void ABaseCharacter::RemovePassiveAbility(const FActiveGameplayEffectHandle EffectHandle,  const int AmountToRemove)
{
	const bool F = AbilitySystemComponent->RemoveActiveGameplayEffect(EffectHandle, AmountToRemove);
}

void ABaseCharacter::OnTakeDamage_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("I have been called DAMAGE EVENT"));
}

void ABaseCharacter::Parry()
{
	bIsParried = true;
	GetWorld()->GetTimerManager().SetTimer(ParryTimerHandle, this, &ABaseCharacter::StopBeingParried, 0.3f, false);
}

void ABaseCharacter::StopBeingParried()
{
	bIsParried = false;
}

float ABaseCharacter::InternalTakeRadialDamage(float Damage, FRadialDamageEvent const& RadialDamageEvent,
                                               AController* EventInstigator, AActor* DamageCauser)
{
	return Super::InternalTakeRadialDamage(Damage, RadialDamageEvent, EventInstigator, DamageCauser);
}


void ABaseCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Movement
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSides"), this, &ABaseCharacter::MoveSides);

	// jump
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABaseCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this , &ACharacter::StopJumping);
	
	if(AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			"ERivetAbilityInputID",
			static_cast<int32>(ERivetAbilityInputID::Confirm),
			static_cast<int32>(ERivetAbilityInputID::Cancel)
			);
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}


FGameplayTagContainer ABaseCharacter::GetPlayerTags()
{
	FGameplayTagContainer Container;
	AbilitySystemComponent->GetOwnedGameplayTags(Container);
	return Container;
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	if(AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm",
			"Cancel",
			"ERivetAbilityInputID",
			static_cast<int32>(ERivetAbilityInputID::Confirm),
			static_cast<int32>(ERivetAbilityInputID::Cancel)
			);
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
		
	}
}



UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);
	if( GetLocalRole() == ROLE_Authority && !bAbilitiesInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("I have been called"))
		for( const TSubclassOf<URivetGameplayAbility>& Ability : GameplayAbilities )
		{
			AddActiveAbility(Ability);
		}
		
		for( const TSubclassOf<UGameplayEffect>& Effect : PassiveGameplayEffects )
		{
			AddPassiveEffect(Effect);
		}
		bAbilitiesInitialized = true;	
	}
}
