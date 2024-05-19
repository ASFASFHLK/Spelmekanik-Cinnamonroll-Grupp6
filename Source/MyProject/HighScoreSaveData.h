// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighScoreSaveData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHighScoreData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	FText NameOfPlayer;
	UPROPERTY(BlueprintReadWrite)
	int32 RoundReached = 0;
	UPROPERTY(BlueprintReadWrite)
	float PlayTime = 0;
	UPROPERTY(BlueprintReadWrite)
	FDateTime TimeOfRecord;
};

UCLASS(Blueprintable)
class MYPROJECT_API UHighScoreSaveData : public USaveGame
{

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FHighScoreData> HighScores;
	
	UFUNCTION(BlueprintCallable)
	TArray<FHighScoreData> GetSortedListOfHighScores(const int CutOff = 5);
	UFUNCTION(BlueprintCallable)
	void AddHighScoreItem(const FHighScoreData &HighScore);
	
};
