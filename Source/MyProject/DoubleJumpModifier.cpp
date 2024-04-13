// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleJumpModifier.h"

#include "PlayerCharacter.h"

void ADoubleJumpModifier::OnAdded()
{
	Super::OnAdded();
	OriginalNumberOfJumps = PlayerCharacter->JumpMaxCount;
	PlayerCharacter->JumpMaxCount = NumberOfJumps;
}

void ADoubleJumpModifier::OnRemoved()
{
	PlayerCharacter->JumpMaxCount = OriginalNumberOfJumps;
	Super::OnRemoved();
}
