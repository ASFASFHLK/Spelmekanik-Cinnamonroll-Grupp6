// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseModifier.h"
#include "BunnyJump.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ABunnyJump : public ABaseModifier
{
public:
	virtual void OnAdded() override;
	virtual  void OnUpdate(float DeltaTime) override;
	
private:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1050.0;
	UPROPERTY(EditAnywhere)
	float Timing = 0.4;
	float Accumulator = 0;
	UPROPERTY(EditAnywhere)
	float SpeedInc = 100;
	float CurrentSpeedInc = 0;
	UPROPERTY()
	class UCharacterMovementComponent* MovementComponent;

	float DefaultSpeed = 0;
	bool SpeedAdded = false; 
	
};
