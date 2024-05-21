// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "Squad.generated.h"

class ADefaultGamemode;
class AEnemy_Spawner;
class AExplosiveEnemy;
class ASquadManager;
class ABaseEnemy;

UCLASS()
class MYPROJECT_API ASquad : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	ASquad();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void RemoveFromSquad(ABaseEnemy* EnemyToRemove);

	UFUNCTION(BlueprintCallable)
	void ExplodeAllEnemies();

	
	UFUNCTION(BlueprintCallable)
	void AddExplosiveToSquad(AExplosiveEnemy* EnemyToAdd);

	UFUNCTION()
	AExplosiveEnemy* LookForExplosiveToThrow();
	
	UFUNCTION()
	FVector GetPlayerLocation() const {return PlayerLocation;}

	UFUNCTION(BlueprintCallable)
	bool CanSpawnExplosive();


private:
	
	UPROPERTY(VisibleAnywhere, Category = "Squad")
	TArray<ABaseEnemy*> SquadMembers;
	
	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	TArray<TSubclassOf<ABaseEnemy>> EnemyTypes;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AExplosiveEnemy*> ExplosiveEnemies;

	UPROPERTY(VisibleAnywhere)
	APawn* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere)
	AEnemy_Spawner* EnemySpawner;

	UPROPERTY()
	ADefaultGamemode* GameMode;

	UPROPERTY()
	FVector Temp;

	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	int NumberOfExplosivesAllowed;
};
