// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "DefaultGamemode.h"
#include "GunBase.h"
#include "HealthComp.h"
#include "ModifierComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

void APlayerCharacter::Reload()
{
	bCanShoot = true;
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
	UWorld* const World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = Cast<APlayerController>(this->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		for (int b = 0; b < Bursts; ++b)
		{
			for (int i = 0; i < Pellets; ++i)
			{
				FRotator Spread = FRotator::ZeroRotator;
				float XSpread = FMath::RandRange(0.f, 30.f);
				float YSpread = FMath::RandRange(0.f, 30.f);
				float ZSpread = FMath::RandRange(0.f, 30.f);
				Spread.Roll = XSpread;
				Spread.Pitch = YSpread;
				Spread.Yaw = ZSpread;
				QueryParams.AddIgnoredActor(PlayerController->GetPawn());
				World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + ((SpawnRotation.Vector() + Spread.Vector()) * 3000), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + ((SpawnRotation.Vector() + Spread.Vector()) * 3000), FColor::Red, false, 1.5f);
				if(!HitResult.GetActor())
				{
					return;
				}
				UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
				HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetController(), this );
			}
			GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &APlayerCharacter::Reload, BurstTime, false);
			if(ShotSound){
				UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
			}
			
			if(ShotEffect){

			}
		}
	}
}

void APlayerCharacter::ShotGunShot()
{
	
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
		if(this == nullptr || this->GetController() == nullptr){
			return;
		}

		if(UWorld* const World = GetWorld()){
			UseShotGun();
			World->GetTimerManager().SetTimer(ShootTimerHandle, this, &APlayerCharacter::Reload, ReloadTime, false);
			bCanShoot = false;
			
		
		}
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
	if(DamageTaken >= HealthComp->GetCurrentHealth())
	{
		Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this))->EndGame(false);
		DisableInput(Cast<APlayerController>(GetController()));
	}
	
	return DamageTaken;
	
}
