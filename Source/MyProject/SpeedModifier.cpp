// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedModifier.h"

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASpeedModifier::OnAdded()
{
	Super::OnAdded();

	OriginalMovementSpeed = PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed;
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = NewMovementSpeed;
}

void ASpeedModifier::OnRemoved()
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = OriginalMovementSpeed;
	Super::OnRemoved();
}
