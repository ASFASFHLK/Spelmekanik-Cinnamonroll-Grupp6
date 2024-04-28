// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "MeleeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMeleeEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:

	
	UFUNCTION(BlueprintNativeEvent)
	void CallPartnerToMove();
	
	UFUNCTION(BlueprintNativeEvent)
	void ThrowExplosiveEnemy();

	UFUNCTION(BlueprintNativeEvent)
	void SetCanThrow(bool Value);

	UFUNCTION(BlueprintCallable)
	void ResetThrowTimer();

	virtual void Tick(float DeltaSeconds) override;

private:
	virtual void BeginPlay() override;
	virtual void Attack() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ThrowTimer;

	UPROPERTY()
	float CurrentThrowTimer;

	
	

};
