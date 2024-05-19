// Fill out your copyright notice in the Description page of Project Settings.


#include "RivetGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool URivetGameInstance::RemoveGameDataFromSlot(const int Slot)
{
	return UGameplayStatics::DeleteGameInSlot(GameDataSlotName, Slot);
}

bool URivetGameInstance::RemoveHighScoreFromSlot(const int Slot)
{
	return UGameplayStatics::DeleteGameInSlot(HighScoreSlotName, Slot);
}


URivetSaveGame* URivetGameInstance::CreateNewGameDataAtSlot(const int Slot)
{
	USaveGame* NewGameData = UGameplayStatics::CreateSaveGameObject(URivetSaveGame::StaticClass());
	SaveGameData = Cast<URivetSaveGame>(NewGameData);
	return SaveGameData; 
}

UHighScoreSaveData* URivetGameInstance::CreateNewHighScoreDataAtSlot(const int Slot)
{
	USaveGame* NewHighScoreData = UGameplayStatics::CreateSaveGameObject(UHighScoreSaveData::StaticClass());
	HighScoreData = Cast<UHighScoreSaveData>(NewHighScoreData);
	return HighScoreData; 
}

URivetSaveGame* URivetGameInstance::LoadSaveGameFromSlot(const int Slot)
{
	USaveGame* Game = UGameplayStatics::LoadGameFromSlot(GameDataSlotName, Slot);
	
	if(Game == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find save data in slot %d"), Slot)
		return nullptr;
	}
	SaveGameData = Cast<URivetSaveGame>(Game);
	
	if(SaveGameData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not convert save data to URivetData in slot %d"), Slot)
	}
	
	return SaveGameData; 
}

UHighScoreSaveData* URivetGameInstance::LoadHighScores(const int Slot)
{

	USaveGame* Game = UGameplayStatics::LoadGameFromSlot(HighScoreSlotName, Slot);

	
	if(Game == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find HighScore data in slot %d"), Slot)
		return nullptr;
	}
	
	HighScoreData = Cast<UHighScoreSaveData>(Game);

	
	if(HighScoreData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not convert save data to UHighScoreData in slot %d"), Slot)
	}
	
	return HighScoreData; 
	
}

bool URivetGameInstance::DoesGameDataExist(const int Slot)
{
	return UGameplayStatics::DoesSaveGameExist(GameDataSlotName, Slot);
}

bool URivetGameInstance::DoesHighScoreDataExist(const int Slot)
{
	return UGameplayStatics::DoesSaveGameExist(HighScoreSlotName, Slot);
}

bool URivetGameInstance::SaveGameDataToSlot( URivetSaveGame* GameData, const int Slot)
{
	const bool Saved = UGameplayStatics::SaveGameToSlot(GameData, GameDataSlotName, Slot);
	return Saved; 
}

bool URivetGameInstance::SaveHighScoreDataToSlot(UHighScoreSaveData* HighScore, const int Slot)
{
	const bool Saved = UGameplayStatics::SaveGameToSlot(HighScore, HighScoreSlotName, Slot);
	return Saved; 
}


