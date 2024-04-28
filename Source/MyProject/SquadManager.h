// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Squad.h"
#include "GameFramework/Actor.h"
#include "SquadManager.generated.h"

class AEnemy_Spawner;
class ASquad;

UCLASS()
class MYPROJECT_API ASquadManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquadManager();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool AssignNewPartner(ABaseEnemy* EnemyToAssign, ASquad* OriginalSquad);

	void SquadDied(ASquad* SquadThatDied);

	void AddSquad(ASquad* SquadToAdd);
	
	void StartNextWave();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	int NumberOfSquads;

	UPROPERTY(VisibleAnywhere, Category = "Squad")
	TArray<ASquad*> MySquads;

	UPROPERTY()
	AEnemy_Spawner* EnemySpawner;

	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	int NumbersOfSquadsThatNeedToDie = 7;
	UPROPERTY(VisibleAnywhere, Category = "Squad")
	int SquadsThatHaveDied = 0;
	
};
