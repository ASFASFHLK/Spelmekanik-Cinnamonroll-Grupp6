// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HighScoreSaveData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHighScoreData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadOnly)
	FText NameOfPlayer;
	UPROPERTY(BlueprintReadOnly)
	int32 RoundReached;
	UPROPERTY(BlueprintReadOnly)
	float PlayTime;
	UPROPERTY(BlueprintReadOnly)
	FDateTime TimeOfRecord;
};

UCLASS()
class MYPROJECT_API UHighScoreSaveData : public USaveGame
{

	GENERATED_BODY()
	TArray<FHighScoreData> HighScores;
public:
	UFUNCTION(BlueprintCallable)
	TArray<FHighScoreData> GetSortedListOfHighScores(const int CutOff = 5);

};
