// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseModifier.h"
#include "ChronoLockModifier.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AChronoLockModifier : public ABaseModifier
{
	GENERATED_BODY()

	virtual void OnAdded() override;
	virtual void OnUpdate(float DeltaTime) override;

	

private:
	void SlowDownTime();
	void RevertToNormalTime();
	
	UPROPERTY(EditAnywhere, Category = "Ability")
	float SlowDownAmount;

	UFUNCTION(BlueprintCallable)
	float GetPercent();

	UPROPERTY(EditAnywhere, Category = "Ability")
	float AmountOfTime;
	
	UPROPERTY()
	float CurrentTimer;

	UPROPERTY()
	bool IsActivated;

	UPROPERTY()
	float AdjustedTime;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	UInputAction* IaSpecialAbility;
	
};
