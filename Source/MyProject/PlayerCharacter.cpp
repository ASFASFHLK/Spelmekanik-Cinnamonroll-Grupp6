// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "DefaultGamemode.h"
#include "GunBase.h"
#include "HealthComp.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

void APlayerCharacter::Fire()
{
	if(!EquipedGun)
	{
		return;
	}
	
	
	
}

void APlayerCharacter::LookUp(float Value)
{

	if (Controller == nullptr or Value == 0.0f)
	{
		return;
	}
	
	if(InvertCamera)
	{
		Value = Value * -1;
	}
	AddControllerPitchInput(Value * LookUpSpeed);

	
}

void APlayerCharacter::LookSides(float Value)
{
	if (Controller == nullptr or Value == 0.0f)
	{
		return;
	}

	AddControllerYawInput(Value * LookSideSpeed);
	
}

// should be moved the gunbase class 
void APlayerCharacter::Shoot()


{	//Character = Cast<AActor*>(this->GetOwner());
	if(this == nullptr || this->GetController() == nullptr){
		return;
	}

	UWorld* const World = GetWorld();
	if(World){
		APlayerController* PlayerController = Cast<APlayerController>(this->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(PlayerController->GetPawn());
		FHitResult HitResult;
		World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * 3000), ECollisionChannel::ECC_Pawn, QueryParams);
		DrawDebugLine(World, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * 3000), FColor::Red, false, 1.5f);

		if(ShotSound){
			UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
		}
		
		if(ShotEffect){

		}
		
		if(!HitResult.GetActor())
		{
			return;
		}
		UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
		HitResult.GetActor()->TakeDamage(10.f, FDamageEvent(),GetController(), this );
		
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
	// Sets the default position 
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
	
	if(DamageTaken >= HealthComp->GetCurrentHealth())
	{
		Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this))->EndGame(false);
		DisableInput(Cast<APlayerController>(GetController()));
	}
	
	return DamageTaken;
	
}
