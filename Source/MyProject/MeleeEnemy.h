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

	UFUNCTION(BlueprintCallable)
	void SpawnExplosiveEnemy();

	UFUNCTION()
	int32 GetGorillaType() const {return GorillaTypeInt;}

	UFUNCTION()
	int32 GetSpawnDesire() const {return SpawnerValue;}

	UFUNCTION()
	int32 GetThrowDesire() const {return ThrowerValue;}

	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Attack() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ThrowTimer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseEnemy> ExplosiveEnemy;

	UPROPERTY()
	float CurrentThrowTimer;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	int ThrowerValue;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	int SpawnerValue;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	FString GorillaType;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	int32 GorillaTypeInt;

	UFUNCTION()
	void DecideWhichType();
};
