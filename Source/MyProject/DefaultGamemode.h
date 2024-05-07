// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGamemode.generated.h"

class ASquadManager;
class AEnemy_Spawner;
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

	UFUNCTION(BlueprintNativeEvent)
	void StartShopPhase();
	UFUNCTION(BlueprintCallable)
	void StartNextWave();
	
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WinScreen;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bFirstWave = true;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoseScreen;
	UPROPERTY(VisibleInstanceOnly)
	AEnemy_Spawner* SpawnerRef;
	UPROPERTY(VisibleInstanceOnly)
	ASquadManager* SquadRef;
	
};
