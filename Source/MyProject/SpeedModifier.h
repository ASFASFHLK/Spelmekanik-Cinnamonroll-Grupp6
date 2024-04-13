// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseModifier.h"
#include "SpeedModifier.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASpeedModifier : public ABaseModifier
{
	GENERATED_BODY()

private:
	virtual void OnAdded() override;
	virtual void OnRemoved() override;

	UPROPERTY(EditAnywhere, Category = "Ability")
	float NewMovementSpeed;

	UPROPERTY()
	float OriginalMovementSpeed;
	
};
