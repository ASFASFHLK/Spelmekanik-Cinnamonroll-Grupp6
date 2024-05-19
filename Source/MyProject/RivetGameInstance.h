// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreSaveData.h"
#include "RivetSaveGame.h"
#include "Engine/GameInstance.h"
#include "RivetGameInstance.generated.h"

class URivetSaveGame;
/**
 * 
 */
UCLASS()
class MYPROJECT_API URivetGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	bool RemoveGameDataFromSlot(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool RemoveHighScoreFromSlot(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	URivetSaveGame* CreateNewGameDataAtSlot(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	UHighScoreSaveData* CreateNewHighScoreDataAtSlot(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	URivetSaveGame* LoadSaveGameFromSlot(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	UHighScoreSaveData* LoadHighScores(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool DoesGameDataExist(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool DoesHighScoreDataExist(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	bool SaveGameDataToSlot(URivetSaveGame* GameData, const int Slot = 0 );

	UFUNCTION(BlueprintCallable)
	bool SaveHighScoreDataToSlot(UHighScoreSaveData* HighScore, const int Slot = 0);
	
	UPROPERTY(EditDefaultsOnly)
	FString GameDataSlotName = "GameData";

	UPROPERTY(EditDefaultsOnly)
	FString HighScoreSlotName = "HighScore";

	UPROPERTY(EditDefaultsOnly)
	FString Unlocks = "Unlocks";
	
public:
	UPROPERTY(BlueprintReadOnly)
	URivetSaveGame* SaveGameData;

	UPROPERTY(BlueprintReadOnly)
	UHighScoreSaveData* HighScoreData;
	
	UPROPERTY(BlueprintReadWrite)
	bool Tutorial = false;
};
