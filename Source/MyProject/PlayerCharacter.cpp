// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "DefaultGamemode.h"
#include "GunBase.h"
#include "HealthComp.h"
#include "ModifierComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void APlayerCharacter::SetGun(AGunBase* NewGun)
{
	Gun = NewGun;
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

void APlayerCharacter::Shoot() const
{
	//UE_LOG(LogTemp, Warning, TEXT("Trying to shoot"));
	if(Gun)
	{
		Gun->Shoot();
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->AirControl = AirTime;
	DefaultMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
	if(ModifierComponent != nullptr)
	{
		ModifierComponent->SetUp(); // prevents a de-sync 
	}


}

void APlayerCharacter::ShowHud(const bool Show)
{

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
	Gun = CreateDefaultSubobject<AGunBase>(TEXT("Gun"));
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
	OnTakeDamage();
	//OnDamage();
	return DamageTaken;
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}
