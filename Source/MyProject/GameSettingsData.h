// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSettingsData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FKeyBindData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	FText NameOfPlayer;
};

UCLASS()
class MYPROJECT_API UGameSettingsData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FKeyBindData KeyBinds; 
	UPROPERTY(BlueprintReadWrite)
	float MouseSense = 2;
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName = "Rivet";
	UPROPERTY(BlueprintReadWrite)
	bool InvertedMouse = false;
	UPROPERTY(BlueprintReadWrite)
	float AudioVolume = 1; 
};
