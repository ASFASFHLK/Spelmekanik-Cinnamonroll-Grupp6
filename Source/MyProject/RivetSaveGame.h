// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RivetSaveGame.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSaveGameData
{
	GENERATED_USTRUCT_BODY()

	FSaveGameData()
	{
		CurrentHealth = 100;
		CurrentCredits = 0;
		CurrentRound = 1;
		BoughtUpgradeSlots = 0;
		PlayTime = 0;
		WorldPos = FVector::ZeroVector;
		CharacterRotator = FRotator::ZeroRotator;
		PlayerName = "Rivet";
	}

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentHealth;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentCredits;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentRound;

	UPROPERTY(BlueprintReadWrite)
	int32 BoughtUpgradeSlots;

	UPROPERTY(BlueprintReadWrite)
	FVector WorldPos;

	UPROPERTY(BlueprintReadWrite)
	FRotator CharacterRotator;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Upgrades;

	UPROPERTY(BlueprintReadWrite)
	float PlayTime;
	
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;
	
	UPROPERTY(BlueprintReadWrite)
	FString WeaponSkin;
};

USTRUCT(BlueprintType)
struct FUnlocks
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	TArray<FText> Unlocks;
	UPROPERTY(BlueprintReadWrite)
	FDateTime UnlockDate;
};

UCLASS()
class MYPROJECT_API URivetSaveGame : public USaveGame
{

	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FSaveGameData SaveData;
	UFUNCTION(BlueprintCallable)
	void AddPassiveEffectRowName(const FString RowName);
	UFUNCTION(BlueprintCallable)
	bool ValidSaveData();
	UFUNCTION(BlueprintCallable)
	void ClearPassiveUpgrades();
	
	FUnlocks Unlocks;
};
