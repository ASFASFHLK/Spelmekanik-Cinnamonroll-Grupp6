// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGamemode.generated.h"

class ASquad;
class AEnemy_Spawner;
class APlayerCharacter;
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
	UFUNCTION(BlueprintNativeEvent)
	void OnSpawnNewWave();

	UFUNCTION(BlueprintNativeEvent)
	void EnemyDied();

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

	UFUNCTION(BlueprintCallable)
	void IncreaseAmountOfEnemies(int Amount);

	UFUNCTION()
	void OnEnemyKilled();

	virtual void BeginPlay() override;

	UFUNCTION()
	bool GetTutorial() const {return Tutorial;}

	UFUNCTION()
	int GetTutorialStep() const {return TutorialStep;}
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartTutorial();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartRoundGameMode();

	UFUNCTION(BlueprintNativeEvent)
	void StartOptionsMenu();

	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WinScreen;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoseScreen;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	AEnemy_Spawner* SpawnerRef;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	ASquad* SquadRef;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bFirstWave = true;

	UPROPERTY(EditDefaultsOnly)
	float EnemyScaling;
	
	UPROPERTY(VisibleInstanceOnly)
	int CurrentAmountOfCredits = 0;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int RoundAmount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int AmountToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int AmountToKill;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int CurrentAmountKilled;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	bool Tutorial = true;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int TutorialStep = 0;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	int EnemiesToKillInTutorial = 0;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	APlayerCharacter* PlayerCharacter;
	
	
};
