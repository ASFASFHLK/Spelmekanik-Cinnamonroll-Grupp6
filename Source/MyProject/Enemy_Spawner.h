// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Spawner.generated.h"

UCLASS()
class MYPROJECT_API AEnemy_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Spawner();
	UFUNCTION()
	void SpawnEnemy();

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FVector SpawnLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseEnemy> EnemyTypeOne;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseEnemy> EnemyTypeTwo;

	UPROPERTY(VisibleInstanceOnly)
	int AmountOfEnemiesSpawned = 0;

	UPROPERTY(VisibleInstanceOnly)
	int AmountOfEnemiesKilled = 0;
	
	UPROPERTY(EditDefaultsOnly)
	int EnemiesToKill = 10;

	UFUNCTION()
	void OnDeathEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
