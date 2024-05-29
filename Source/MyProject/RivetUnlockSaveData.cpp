// Fill out your copyright notice in the Description page of Project Settings.


#include "RivetUnlockSaveData.h"

void URivetUnlockSaveData::AddUnlockedItem(const FString NameOfRow)
{
	UnlockedItems.Add(NameOfRow);
}

bool URivetUnlockSaveData::HasItem(const FString NameOfRow)
{
	return UnlockedItems.Contains(NameOfRow);
}

void URivetUnlockSaveData::RemoveAllUnlocks()
{
	UnlockedItems.Empty();
}

bool URivetUnlockSaveData::RemoveUnlockedItem(const FString NameOfRow)
{
	const int ItemsRemoved = UnlockedItems.Remove(NameOfRow);
	return ItemsRemoved > 0;
}
