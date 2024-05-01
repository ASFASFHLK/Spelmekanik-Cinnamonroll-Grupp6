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
	if(PlayerCharacter->DefaultMovementSpeed > MaxSpeed) // prevents bjump from being a nerf when an speed buff is active 
	{
		return;
	}
	
	if(MovementComponent->IsFalling()) // will have the funny side effect of adding speed when falling 
	{
		Accumulator = 0;
		if(MovementComponent->MaxWalkSpeed == MaxSpeed or SpeedAdded)
		{
			return;
		}
		SpeedAdded = true;
		UE_LOG(LogTemp, Warning, TEXT("Adding speed"))
		CurrentSpeedInc+= SpeedInc;

		MovementComponent->MaxWalkSpeed+= SpeedInc;
		if(MovementComponent->MaxWalkSpeed > MaxSpeed) // fixes a bug that can cause us to go faster than we are allowed to 
		{
			UE_LOG(LogTemp, Warning, TEXT("SpeedInc Vs MaxSpeed %f : %f"), CurrentSpeedInc, MaxSpeed)
			MovementComponent->MaxWalkSpeed = MaxSpeed;
		}
	}
	else
	{
		Accumulator+= DeltaTime;
		if(Accumulator > Timing && CurrentSpeedInc > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Reseting speed"))
			CurrentSpeedInc = 0;
			//Accumulator = 0;
			UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed %f ResetSpeed %f"),MovementComponent->MaxWalkSpeed, PlayerCharacter->DefaultMovementSpeed )
			MovementComponent->MaxWalkSpeed = PlayerCharacter->DefaultMovementSpeed;
			UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed %f ResetSpeed %f"),MovementComponent->MaxWalkSpeed, PlayerCharacter->DefaultMovementSpeed )
			
		}
		SpeedAdded = false;
	}
	
}
