// Fill out your copyright notice in the Description page of Project Settings.


#include "RivetSaveGame.h"

void URivetSaveGame::AddPassiveEffectRowName(const FString RowName)
{
	SaveData.Upgrades.Add(RowName);
}

bool URivetSaveGame::ValidSaveData()
{
	return SaveData.CurrentRound > 1;
}

void URivetSaveGame::ClearPassiveUpgrades()
{
	SaveData.Upgrades.Empty();
}
