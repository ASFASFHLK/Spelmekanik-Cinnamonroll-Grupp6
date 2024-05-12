// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGamemode.generated.h"

class ASquadManager;
class AEnemy_Spawner;
/**
 * 
 */
UCLASS()
class MYPROJECT_API ADefaultGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void EndGame(bool PlayerWin);

	UFUNCTION(BlueprintNativeEvent)
	void StartShopPhase();
	UFUNCTION(BlueprintCallable)
	void StartNextWave();

	// Credit Related
	UFUNCTION(BlueprintPure)
	int GetAmountOfCredits() const;
	void SetAmountOfCredits(const int AmountToSet);
	UFUNCTION(BlueprintPure)
	bool CanAfford(const int PriceToCheck) const;
	UFUNCTION(BlueprintCallable)
	void AddCredits(const int AmountToAdd);
	UFUNCTION(BlueprintCallable)
	void ResetCredits();
	UFUNCTION(BlueprintCallable)
	void RemoveCredits(const int AmountToRemove);
	UFUNCTION(BlueprintCallable)
	bool RemoveIfWeCanAfford(const int PriceToCheck);
	

	UFUNCTION(BlueprintNativeEvent)
	void StartOptionsMenu();

	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WinScreen;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoseScreen;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	AEnemy_Spawner* SpawnerRef;
	UPROPERTY(VisibleInstanceOnly)
	ASquadManager* SquadRef;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bFirstWave = true;

	UPROPERTY(EditDefaultsOnly)
	float EnemyScaling;
	
	UPROPERTY(VisibleInstanceOnly)
	int CurrentAmountOfCredits = 0;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int RoundAmount = 1;
	
};
