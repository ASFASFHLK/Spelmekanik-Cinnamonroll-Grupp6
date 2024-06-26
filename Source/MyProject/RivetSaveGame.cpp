// Fill out your copyright notice in the Description page of Project Settings.


#include "RivetSaveGame.h"

void URivetSaveGame::AddPassiveEffectRowName(const FString RowName)
{
	SaveData.Upgrades.Add(RowName);
}

bool URivetSaveGame::ValidSaveData()
{
	return SaveData.CurrentRound > 1 && IsSaveDataValid;
}

void URivetSaveGame::ClearPassiveUpgrades()
{
	SaveData.Upgrades.Empty();
}

void URivetSaveGame::SetPlayerName(const FString NameOfPlayer)
{
	if(NameOfPlayer == "")
	{
		SaveData.PlayerName = "Rivet";
		return;
	}
	SaveData.PlayerName = NameOfPlayer;
}

void URivetSaveGame::SetWeaponSkin(const FString WeaponSkin)
{
	SaveData.WeaponSkin = WeaponSkin;
}

void URivetSaveGame::ClearShopItems()
{
	CurrentShopItems.Empty();
}

void URivetSaveGame::UpdateSaveData(const int CurrentHealth, const int CurrentCredits, const int CurrentRound,
                                    const int BoughtUpgradeSlots, const FVector& WorldPos, const FRotator& CharacterRotator, const FString PlayerName,
                                    const float PlayTime)
{
	SaveData.CurrentHealth = CurrentHealth;
	SaveData.CurrentCredits = CurrentCredits;
	SaveData.CurrentRound = CurrentRound;
	SaveData.BoughtUpgradeSlots = BoughtUpgradeSlots;
	SaveData.WorldPos = WorldPos;
	SaveData.CharacterRotator = CharacterRotator;
	if(PlayerName != "")
	{
		SaveData.PlayerName = PlayerName;
	}
	SaveData.PlayTime = PlayTime;
}
