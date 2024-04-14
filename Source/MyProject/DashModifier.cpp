// Fill out your copyright notice in the Description page of Project Settings.


#include "DashModifier.h"

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ADashModifier::OnAdded()
{
	Super::OnAdded();

	PlayerCharacter->InputComponent->BindAction("Dash", IE_Pressed, this, &ADashModifier::Dash);
	Timer = 0;
}

void ADashModifier::OnRemoved()
{
	Super::OnRemoved();
}

void ADashModifier::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);
	
	if(IsDashing)
	{
		Timer -= DeltaTime;
		if(Timer <= 0)
		{
			IsDashing = false;
		}
	}
}

void ADashModifier::Dash()
{
	if(!IsDashing)
	{
		const FVector ForwardDirection = PlayerCharacter->GetActorRotation().Vector();
		PlayerCharacter->LaunchCharacter(ForwardDirection * DashDistance, true, true);
		Timer = DashCoolDown;
		IsDashing = true;
	}
}
