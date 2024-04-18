// Fill out your copyright notice in the Description page of Project Settings.


#include "BunnyJump.h"

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABunnyJump::OnAdded()
{
	Super::OnAdded();
	MovementComponent = PlayerCharacter->GetCharacterMovement();
	DefaultSpeed = MovementComponent->MaxWalkSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Default speed %f"), DefaultSpeed)
}

void ABunnyJump::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	if(MovementComponent->IsFalling())
	{
		if(CurrentSpeedInc >= MaxSpeed or SpeedAdded)
		{
			return;
		}
		SpeedAdded = true;
		UE_LOG(LogTemp, Warning, TEXT("Adding speed"))
		CurrentSpeedInc+= SpeedInc;
		MovementComponent->MaxWalkSpeed+= SpeedInc;
		Accumulator = 0;
	}
	else
	{
		Accumulator+= DeltaTime;
		if(Accumulator > Timing)
		{
			UE_LOG(LogTemp, Warning, TEXT("Reseting speed"))
			CurrentSpeedInc = 0;
			Accumulator = 0;
			MovementComponent->MaxWalkSpeed = DefaultSpeed;
		}
		SpeedAdded = false;
	}
	
}
