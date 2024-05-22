// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HighScoreSaveData.h"
#include "RivetSaveGame.h"
#include "Engine/GameInstance.h"
#include "RivetGameInstance.generated.h"

class UGameSettingsData;
class URivetSaveGame;
/**
 * 
 */
UCLASS()
class MYPROJECT_API URivetGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	URivetSaveGame* LoadOrNewGameSaveData(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	UHighScoreSaveData* LoadOrNewHighScoreSaveData(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	UGameSettingsData* LoadOrNewGameSettingsData(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveGameDataFromSlot(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool RemoveHighScoreFromSlot(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool RemoveGameSettingsDataFromSlot(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	URivetSaveGame* CreateNewGameDataAtSlot(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	UHighScoreSaveData* CreateNewHighScoreDataAtSlot(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	UGameSettingsData* CreateNewGameSettingsDataAtSlot(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	URivetSaveGame* LoadSaveGameFromSlot(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	UHighScoreSaveData* LoadHighScoresFromSlot(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	UGameSettingsData* LoadGameSettingsDataFromSlot(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool DoesGameDataExist(const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool DoesHighScoreDataExist(const int Slot = 0);
	
	UFUNCTION(BlueprintCallable)
	bool SaveGameDataToSlot(URivetSaveGame* GameData, const int Slot = 0 );
	
	UFUNCTION(BlueprintCallable)
	bool SaveHighScoreDataToSlot(UHighScoreSaveData* HighScore, const int Slot = 0);

	UFUNCTION(BlueprintCallable)
	bool SaveSettingsDataToSlot(UGameSettingsData* Settings, const int Slot = 0);
	
	UPROPERTY(EditDefaultsOnly)
	FString GameDataSlotName = "GameData";

	UPROPERTY(EditDefaultsOnly)
	FString HighScoreSlotName = "HighScore";

	UPROPERTY(EditDefaultsOnly)
	FString UnlocksSlotName = "Unlocks";

	UPROPERTY(EditDefaultsOnly)
	FString GameSettingsSlotName = "Settings";
	
public:
	UPROPERTY(BlueprintReadOnly)
	URivetSaveGame* SaveGameData;

	UPROPERTY(BlueprintReadOnly)
	UHighScoreSaveData* HighScoreData;

	UPROPERTY(BlueprintReadOnly)
	UGameSettingsData* SettingsData;
	
	UPROPERTY(BlueprintReadWrite)
	bool Tutorial = false;
};
