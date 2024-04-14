// Fill out your copyright notice in the Description page of Project Settings.


#include "ChronoLockModifier.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

class UEnhancedInputLocalPlayerSubsystem;

void AChronoLockModifier::OnAdded()
{
	Super::OnAdded();
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerCharacter->InputComponent);
	
	EnhancedInputComponent->BindAction(IaSpecialAbility, ETriggerEvent::Triggered,
		this, &AChronoLockModifier::SlowDownTime);
	EnhancedInputComponent->BindAction(IaSpecialAbility,ETriggerEvent::Completed,
		this, &AChronoLockModifier::RevertToNormalTime);

	CurrentTimer = AmountOfTime;
}

void AChronoLockModifier::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);
	
	AdjustedTime = DeltaTime / UGameplayStatics::GetGlobalTimeDilation(this);
	if(CurrentTimer < AmountOfTime && !IsActivated)
	{
		CurrentTimer += AdjustedTime;
	}else if (CurrentTimer <= 0)
	{
		RevertToNormalTime();
	}else if(IsActivated)
	{
		CurrentTimer-= AdjustedTime;
	}
	FString TimerMessage = FString::Printf(TEXT("Slow down time: %f"), CurrentTimer);
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			TimerMessage);	
}


void AChronoLockModifier::SlowDownTime()
{
	IsActivated = true;
	UGameplayStatics::SetGlobalTimeDilation(this, SlowDownAmount);
}

void AChronoLockModifier::RevertToNormalTime()
{
	IsActivated = false;
	UGameplayStatics::SetGlobalTimeDilation(this, 1);
}
