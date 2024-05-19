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
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHealth;
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentCredits;
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentRound;
	UPROPERTY(BlueprintReadOnly)
	int32 BoughtUpgradeSlots;
	UPROPERTY(BlueprintReadOnly)
	FVector WorldPos;
	UPROPERTY(BlueprintReadOnly)
	FRotator CharacterRotator;
	UPROPERTY(BlueprintReadOnly)
	TArray<FText> Upgrades;
	UPROPERTY(BlueprintReadOnly)
	float PlayTime;
	UPROPERTY(BlueprintReadOnly)
	FText WeaponSkin;
};

USTRUCT(BlueprintType)
struct FUnlocks
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadOnly)
	TArray<FText> Unlocks;
	UPROPERTY(BlueprintReadOnly)
	FDateTime UnlockDate;
};

UCLASS()
class MYPROJECT_API URivetSaveGame : public USaveGame
{

	GENERATED_BODY()
	FSaveGameData SaveData;
	FUnlocks Unlocks;
};
