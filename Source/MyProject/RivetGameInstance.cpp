// Fill out your copyright notice in the Description page of Project Settings.

#include "RivetGameInstance.h"
#include "GameSettingsData.h"
#include "RivetUnlockSaveData.h"
#include "Kismet/GameplayStatics.h"

URivetSaveGame* URivetGameInstance::LoadOrNewGameSaveData(const int Slot)
{
	if(SaveGameData == nullptr)
	{
		if(not DoesGameDataExist(Slot) or LoadSaveGameFromSlot(Slot) == nullptr)
		{
			return CreateNewGameDataAtSlot(Slot);
		}
	}
	return SaveGameData;
}

UHighScoreSaveData* URivetGameInstance::LoadOrNewHighScoreSaveData(const int Slot)
{
	if(HighScoreData == nullptr)
	{
		if(not DoesHighScoreDataExist(Slot) or LoadHighScoresFromSlot(Slot) == nullptr)
		{
			return CreateNewHighScoreDataAtSlot(Slot);
		}
	}
	return HighScoreData;
}

UGameSettingsData* URivetGameInstance::LoadOrNewGameSettingsData(const int Slot)
{
	if(SettingsData == nullptr)
	{
		if(not DoesSettingsDataExist(Slot) or LoadGameSettingsDataFromSlot(Slot) == nullptr)
		{
			return CreateNewGameSettingsDataAtSlot(Slot);
		}
	}
	return SettingsData;
}

URivetUnlockSaveData* URivetGameInstance::LoadOrNewUnlockSaveData(const int Slot)
{
	if(UnlockData == nullptr)
	{
		if(not DoesUnlockDataExist(Slot) or LoadUnlockDataFromSlot(Slot) == nullptr)
		{
			return CreateNewUnlockSaveDataAtSlot(Slot);
		}
	}
	return UnlockData;
	
}

bool URivetGameInstance::RemoveGameDataFromSlot(const int Slot)
{
	SaveGameData = nullptr;
	if(!DoesGameDataExist(Slot))
	{
		return UGameplayStatics::DeleteGameInSlot(GameDataSlotName, Slot);
	}
	return false;
}

bool URivetGameInstance::RemoveHighScoreFromSlot(const int Slot)
{
	HighScoreData = nullptr;
	if(!DoesHighScoreDataExist(Slot))
	{
		return UGameplayStatics::DeleteGameInSlot(HighScoreSlotName, Slot);
	}
	return false; 
}

bool URivetGameInstance::RemoveGameSettingsDataFromSlot(const int Slot)
{
	SettingsData = nullptr;
	if(DoesSettingsDataExist(Slot))
	{
		return UGameplayStatics::DeleteGameInSlot(GameSettingsSlotName, Slot);
	}
	return false;
}

bool URivetGameInstance::RemoveUnlockDataFromSlot(const int Slot)
{
	UnlockData = nullptr;
	if(DoesUnlockDataExist(Slot))
	{
		return UGameplayStatics::DeleteGameInSlot(UnlocksSlotName, Slot);
	}
	return false;
	
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

UGameSettingsData* URivetGameInstance::CreateNewGameSettingsDataAtSlot(const int Slot)
{
	USaveGame* NewSettingsData = UGameplayStatics::CreateSaveGameObject(UGameSettingsData::StaticClass());
	SettingsData = Cast<UGameSettingsData>(NewSettingsData);
	return SettingsData; 
}

URivetUnlockSaveData* URivetGameInstance::CreateNewUnlockSaveDataAtSlot(const int Slot)
{
	USaveGame* NewUnlockData = UGameplayStatics::CreateSaveGameObject(URivetUnlockSaveData::StaticClass());
	UnlockData = Cast<URivetUnlockSaveData>(NewUnlockData);
	return  UnlockData;
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

UHighScoreSaveData* URivetGameInstance::LoadHighScoresFromSlot(const int Slot)
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

UGameSettingsData* URivetGameInstance::LoadGameSettingsDataFromSlot(const int Slot)
{
	USaveGame* SaveData = UGameplayStatics::LoadGameFromSlot(GameSettingsSlotName, Slot);

	
	if(SaveData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find Settings data in slot %d"), Slot)
		return nullptr;
	}
	
	SettingsData = Cast<UGameSettingsData>(SaveData);

	
	if(SettingsData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not convert save data to UGameSettingsData in slot %d"), Slot)
	}
	
	return SettingsData; 
}

URivetUnlockSaveData* URivetGameInstance::LoadUnlockDataFromSlot(const int Slot)
{
	USaveGame* SaveData = UGameplayStatics::LoadGameFromSlot(UnlocksSlotName, Slot);

	
	if(SaveData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find UnlockData data in slot %d"), Slot)
		return nullptr;
	}
	
	UnlockData = Cast<URivetUnlockSaveData>(SaveData);

	
	if(UnlockData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not convert save data to UGameSettingsData in slot %d"), Slot)
	}
	
	return UnlockData; 
}

bool URivetGameInstance::DoesGameDataExist(const int Slot)
{
	return UGameplayStatics::DoesSaveGameExist(GameDataSlotName, Slot);
}

bool URivetGameInstance::DoesHighScoreDataExist(const int Slot)
{
	return UGameplayStatics::DoesSaveGameExist(HighScoreSlotName, Slot);
}

bool URivetGameInstance::DoesSettingsDataExist(const int Slot)
{
	return UGameplayStatics::DoesSaveGameExist(GameSettingsSlotName, Slot);
}

bool URivetGameInstance::DoesUnlockDataExist(const int Slot)
{
	return UGameplayStatics::DoesSaveGameExist(UnlocksSlotName, Slot);
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

bool URivetGameInstance::SaveSettingsDataToSlot(UGameSettingsData* Settings, const int Slot)
{
	const bool Saved = UGameplayStatics::SaveGameToSlot(Settings, GameSettingsSlotName, Slot);
	return Saved; 
}

bool URivetGameInstance::SaveUnlockDataToSlot(URivetUnlockSaveData* UnlockSaveData, const int Slot)
{
	const bool Saved = UGameplayStatics::SaveGameToSlot(UnlockSaveData, UnlocksSlotName, Slot);
	return Saved; 
}