// Fill out your copyright notice in the Description page of Project Settings.


#include "BunnyJump.h"

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABunnyJump::OnAdded()
{
	Super::OnAdded();
	MovementComponent = PlayerCharacter->GetCharacterMovement();
}

void ABunnyJump::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	if(MovementComponent->IsFalling()) // will have the funny side effect of adding speed when falling 
	{
		Accumulator = 0;
		if(CurrentSpeedInc >= MaxSpeed or SpeedAdded)
		{
			return;
		}
		SpeedAdded = true;
		UE_LOG(LogTemp, Warning, TEXT("Adding speed"))
		CurrentSpeedInc+= SpeedInc;
		if(CurrentSpeedInc > MaxSpeed) // fixes a bug that can cause us to go faster than we are allowed to 
		{
			MovementComponent->MaxWalkSpeed = MaxSpeed;
			return;
		}
		
		MovementComponent->MaxWalkSpeed+= SpeedInc;
	}
	else
	{
		Accumulator+= DeltaTime;
		if(Accumulator > Timing && CurrentSpeedInc > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Reseting speed"))
			CurrentSpeedInc = 0;
			//Accumulator = 0;
			MovementComponent->MaxWalkSpeed = PlayerCharacter->DefaultMovementSpeed;
		}
		SpeedAdded = false;
	}
	
}
