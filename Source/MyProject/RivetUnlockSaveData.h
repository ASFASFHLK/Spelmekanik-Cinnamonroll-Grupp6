// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RivetUnlockSaveData.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API URivetUnlockSaveData : public USaveGame
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TArray<FString> UnlockedItems;
	
	UFUNCTION(BlueprintCallable)
	void AddUnlockedItem(const FString NameOfRow);

	UFUNCTION(BlueprintCallable)
	bool HasItem(const FString NameOfRow); 

	UFUNCTION(BlueprintCallable)
	void RemoveAllUnlocks();

	UFUNCTION(BlueprintCallable)
	bool RemoveUnlockedItem(const FString NameOfRow);
	
};
