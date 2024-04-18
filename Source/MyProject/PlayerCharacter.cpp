// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "DefaultGamemode.h"
#include "GunBase.h"
#include "HealthComp.h"
#include "ModifierComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void APlayerCharacter::Reload()
{
	bCanShoot = true;
	BurstCheck = 0;
	UE_LOG(LogTemp, Warning, TEXT("Can shoot"));
}

void APlayerCharacter::Fire()
{
	if(!EquipedGun)
	{
		return;
	}
}

void APlayerCharacter::UseShotGun()
{
	UE_LOG(LogTemp, Warning, TEXT("I set off a timer"));
	if(BurstCheck == 0 && !bCanceledShot) //crashed after this was added
	{
		++BurstCheck;
		UE_LOG(LogTemp, Warning, TEXT("First shot = %i"), BurstCheck);//crash
		ShotGunShot();
		
	}
	if(GetWorld()->GetTimerManager().IsTimerPaused(BurstTimerHandle) && !bCanceledShot)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(BurstTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &APlayerCharacter::ShotGunShot, BurstTime, false);
		++BurstCheck;
		UE_LOG(LogTemp, Warning, TEXT("BurstCheckt = %i"), BurstCheck);
	}
	else if(BurstCheck < Bursts - 1 && !bCanceledShot)
	{
		++BurstCheck;
		UE_LOG(LogTemp, Warning, TEXT("BurstChecknormal = %i"), BurstCheck);
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &APlayerCharacter::ShotGunShot, BurstTime, false);
	}
	// else//not necessary?
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("BurstCheck = %i"), BurstCheck);
	// 	CancelShot();
	// 	GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &APlayerCharacter::Reload, ReloadTime, false);
	// }
}

void APlayerCharacter::ShotGunShot()
{
	UE_LOG(LogTemp, Warning, TEXT("I shot a shot"));
	UWorld* const World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = Cast<APlayerController>(this->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		for (int i = 0; i < Pellets; ++i)
		{
			FRotator Spread = SpawnRotation;
			double XSpread = FMath::RandRange(0.0f, 30.f);
			float YSpread = FMath::RandRange(0.0f, 30.f);
			float ZSpread = FMath::RandRange(0.0f, 30.f);
			Spread.Roll += XSpread;
			Spread.Pitch += YSpread;
			Spread.Yaw += ZSpread;
			QueryParams.AddIgnoredActor(PlayerController->GetPawn());
			World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), FColor::Red, false, 1.5f);//crash
			if(HitResult.GetActor())
			{
				UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
				HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetController(), this );
				if(ShotSound){
					UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
				}
				
				if(ShotEffect){

				}
			}
		}
	}
	UseShotGun();
}

void APlayerCharacter::LookUp(float Value) // Prevents nullptr and invalid input 
{

	if (Controller == nullptr or Value == 0.0f)
	{
		return;
	}
	
	if(InvertCamera) // Inverts camera controls 
	{
		Value = Value * -1;
	}
	
	AddControllerPitchInput(Value * LookUpSpeed);
}

void APlayerCharacter::LookSides(float Value)
{
	if (Controller == nullptr or Value == 0.0f) // Prevents nullptr and invalid input 
	{
		return;
	}

	AddControllerYawInput(Value * LookSideSpeed);
	
}

// should be moved the gunbase class 
void APlayerCharacter::Shoot()
{	//Character = Cast<AActor*>(this->GetOwner());
	if(bCanShoot)
	{
		bCanceledShot = false;
		if(this == nullptr || this->GetController() == nullptr){
			return;
		}
		if(UWorld* const World = GetWorld()){
			UseShotGun();
			bCanShoot = false;
		}
	}
}

void APlayerCharacter::CancelShot()
{
	if(GetWorld())
	{
		if(!bCanceledShot)
		{
			bCanceledShot = true;
			BurstCheck = 0;
			GetWorld()->GetTimerManager().PauseTimer(BurstTimerHandle); 
			GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &APlayerCharacter::Reload, ReloadTime, false);
		}
	}	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->AirControl = AirTime;
	if(ModifierComponent != nullptr)
	{
		ModifierComponent->SetUp(); // prevents a de-sync 
	}
}

APlayerCharacter::APlayerCharacter()
{
	// Sets the default player size 
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Sets up the camera 
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
	CharacterCamera->SetupAttachment(GetCapsuleComponent());
	// Makes the camera rotate with the character
	CharacterCamera->bUsePawnControlRotation = true;
	// Sets the default position of the camera
	CharacterCamera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));

	// Creates the default mesh 
	PlayerFirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	PlayerFirstPersonMesh->SetupAttachment(CharacterCamera);
	PlayerFirstPersonMesh->SetOnlyOwnerSee(true);
	
	// Turns of shadows 
	PlayerFirstPersonMesh->bCastDynamicShadow = false;
	PlayerFirstPersonMesh->CastShadow = false;

	// sets default position
	PlayerFirstPersonMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	ModifierComponent = CreateDefaultSubobject<UModifierComponent>(TEXT("Modifier Component"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookSides);
	//PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &APlayerCharacter::Shoot);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Player Specific Damage handler 
	if( 0 >= HealthComp->GetCurrentHealth())
	{
		Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this))->EndGame(false);
		DisableInput(Cast<APlayerController>(GetController()));
	}
	
	return DamageTaken;
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetCharacterMovement()->IsFalling() && false)
	{
		float mouseX;
		float mouseY;
		const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->GetMousePosition(mouseX, mouseY); // should be cached
		const float AxisValue = PlayerController->GetInputAxisValue( TEXT("LookRight"));
		const float MoveValue = AxisValue * mouseX;

		if(MoveValue > 0.5f)
		{
			
		}
		
	}
	
}
