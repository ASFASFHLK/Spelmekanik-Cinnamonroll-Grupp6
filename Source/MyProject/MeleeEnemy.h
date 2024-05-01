// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "MeleeEnemy.generated.h"

class UBlackboardComponent;
class AExplosiveEnemy;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AMeleeEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:

	/*
	UFUNCTION(BlueprintNativeEvent)
	void CallPartnerToMove();
	*/
	
	UFUNCTION(BlueprintNativeEvent)
	void ThrowExplosiveEnemy();

	UFUNCTION()
	void CallExplosiveToMove();

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

	UFUNCTION()
	AExplosiveEnemy* GetEnemyToThrow() const {return EnemyToThrow;}
	
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Attack() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ThrowOrSpawnTimer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseEnemy> ExplosiveEnemy;

	UPROPERTY()
	float CurrentThrowOrSpawnTimer;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	int ThrowerValue;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	int SpawnerValue;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	FString GorillaType;

	UPROPERTY(VisibleAnywhere, Category = "Type")
	int32 GorillaTypeInt;

	UPROPERTY()
	AExplosiveEnemy* EnemyToThrow;


	
	UFUNCTION()
	void DecideWhichType();
};
