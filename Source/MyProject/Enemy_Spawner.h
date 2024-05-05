// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Spawner.generated.h"


class ASquad;
class ASquadManager;
class ASpawnerGate;




UCLASS()
class MYPROJECT_API AEnemy_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	
	AEnemy_Spawner();
	
	UFUNCTION()
	bool SpawnEnemy();
	
	UFUNCTION()
	void StartNextWave();

protected:
	virtual void BeginPlay() override;

private:
	
	UFUNCTION()
	void OnDeathEvent();

	UPROPERTY(EditAnywhere, Category = "Spawner Settings", BlueprintReadWrite, Meta = (MakeEditWidget = true, AllowPrivateAccess = true))
	TSubclassOf<ASquad> SquadType;
	
	UPROPERTY(EditAnywhere, Category = "Spawner Settings", BlueprintReadWrite, Meta = (MakeEditWidget = true, AllowPrivateAccess = true))
	TArray<TSubclassOf<class ABaseEnemy>> Enemies;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings", BlueprintReadWrite, Meta = (MakeEditWidget = true, AllowPrivateAccess = true))
	int AmountToSpawnAtStart = 4;

	UPROPERTY(EditAnywhere, Category = "Spawner Settings", BlueprintReadWrite, Meta = (MakeEditWidget = true, AllowPrivateAccess = true))
	int AmountOfTotalSquads = 6;
	int AmountOfTotalSquadsToSpawn = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="Spawner Settings", BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	int EnemiesToKill = 10;
	
	UPROPERTY(VisibleInstanceOnly, Category="Spawner Info", BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	int AmountOfEnemiesSpawned = 0;

	UPROPERTY(VisibleInstanceOnly, Category="Spawner Info", BlueprintReadOnly,  meta=(AllowPrivateAccess=true))
	int AmountOfEnemiesKilled = 0;

	UPROPERTY(VisibleAnywhere)
	ASquadManager* SquadManager;

	UPROPERTY(VisibleAnywhere)
	ASquad* Squad;
	UPROPERTY(VisibleAnywhere)
	bool bFirstWave = true;
	int LocationIndex = 0;
	UPROPERTY()
	TArray<ASpawnerGate*> SpawnerGates;

	void GetSpawnGatesInScene();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
