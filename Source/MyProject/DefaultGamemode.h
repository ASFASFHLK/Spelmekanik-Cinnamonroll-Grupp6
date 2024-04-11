// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGamemode.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ADefaultGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void EndGame(bool PlayerWin);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WinScreen;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoseScreen;

	
};
