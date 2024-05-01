// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleJumpModifier.h"

#include "PlayerCharacter.h"


void ADoubleJumpModifier::AddDuplicate()
{
	Super::AddDuplicate();
	AmountsEquipped+=1;
	PlayerCharacter->JumpMaxCount += DuplicateExtraJumps; 
}



void ADoubleJumpModifier::OnAdded()
{
	Super::OnAdded();

	PlayerCharacter->JumpMaxCount += ExtraJumps;
}

void ADoubleJumpModifier::OnRemoved()
{
	PlayerCharacter->JumpMaxCount -= ExtraJumps + (DuplicateExtraJumps * AmountsEquipped-1);

	// prevents us from going below 1 jump
	if(PlayerCharacter->JumpMaxCount  < 1)
	{
		PlayerCharacter->JumpMaxCount = 1; 
	}
	
	Super::OnRemoved();
}


