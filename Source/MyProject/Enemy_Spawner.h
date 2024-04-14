// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Spawner.generated.h"


class ASpawnerGate;




UCLASS()
class MYPROJECT_API AEnemy_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Spawner();
	UFUNCTION()
	void SpawnEnemy();

protected:
	virtual void BeginPlay() override;

private:
	// Called when the game starts or when spawned
	UFUNCTION()
	void OnDeathEvent();
	
	UPROPERTY(EditAnywhere, Category = "Spawner Settings", BlueprintReadWrite, Meta = (MakeEditWidget = true, AllowPrivateAccess = true))
	TArray<TSubclassOf<class ABaseEnemy>> Enemies;

	UPROPERTY(EditDefaultsOnly, Category="Spawner Settings", BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	int AmountToSpawnAtStart = 4;
	
	UPROPERTY(EditDefaultsOnly, Category="Spawner Settings", BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	int EnemiesToKill = 10;
	
	UPROPERTY(VisibleInstanceOnly, Category="Spawner Info", BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	int AmountOfEnemiesSpawned = 0;

	UPROPERTY(VisibleInstanceOnly, Category="Spawner Info", BlueprintReadOnly,  meta=(AllowPrivateAccess=true))
	int AmountOfEnemiesKilled = 0;
	
	int LocationIndex = 0;
	UPROPERTY()
	TArray<ASpawnerGate*> SpawnerGates;

	void GetSpawnGatesInScene();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
