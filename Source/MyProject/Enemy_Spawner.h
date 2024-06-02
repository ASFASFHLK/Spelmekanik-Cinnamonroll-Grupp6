// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Spawner.generated.h"


class ABaseEnemy;
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

	UFUNCTION(BlueprintCallable)
	void SetScaling(const float Value){ScalingValue = Value;}
	
	UFUNCTION(BlueprintCallable)
	bool PlaceEnemiesAtSpawnGates(TSubclassOf<class ABaseEnemy> Enemy);

	UFUNCTION(BlueprintCallable)
	ASquad* GetSquad() const {return Squad;}

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnEnemy(TSubclassOf<class ABaseEnemy> EnemyType, FVector Location, FRotator Rotation, float Scaling);

	//UFUNCTION(BlueprintCallable)
	//void OnDeathEvent();
	
	UFUNCTION(BlueprintCallable)
	void StartNextWave(int Amount);

	UFUNCTION(BlueprintCallable)
	void StartNextCustomWave(TSubclassOf<ABaseEnemy> EnemyType, int Amount);

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "Spawner Settings", BlueprintReadWrite, Meta = (MakeEditWidget = true, AllowPrivateAccess = true))
	TSubclassOf<ASquad> SquadType;
	
	UPROPERTY(EditAnywhere, Category = "Spawner Settings", BlueprintReadWrite, Meta = (MakeEditWidget = true, AllowPrivateAccess = true))
	TArray<TSubclassOf<class ABaseEnemy>> Enemies;
	
	UPROPERTY(VisibleAnywhere)
	ASquad* Squad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	float ScalingDamage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	float ScalingHealth = 1;

	UPROPERTY()
	float ScalingValue;
	
	UPROPERTY()
	int LocationIndex = 0;
	
	UPROPERTY()
	TArray<ASpawnerGate*> SpawnerGates;
	
	UFUNCTION()
	void GetSpawnGatesInScene();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
