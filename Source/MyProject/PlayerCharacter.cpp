// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	
}
