// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Spawner.h"
#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnerGate.h"
#include "SquadManager.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"
#include "Algo/RandomShuffle.h"

// Sets default values
AEnemy_Spawner::AEnemy_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemy_Spawner::IncreaseScaling(float Value)
{
	ScalingHealth += Value;
	ScalingDamage += Value;
}

// Called when the game starts or when spawned
void AEnemy_Spawner::BeginPlay()
{
	Super::BeginPlay();

	GetSpawnGatesInScene();
	//SquadManager = Cast<ASquadManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquadManager::StaticClass()));
	Squad = Cast<ASquad>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquad::StaticClass()));
}




bool AEnemy_Spawner::PlaceEnemiesAtSpawnGates(TSubclassOf<class ABaseEnemy> Enemy)
{
	if(Enemies.Num() < 1 or SpawnerGates.Num() < 1) // prevents indexing into invalid arrays 
	{
		return false;
	}
	ASpawnerGate* SpawnRef = SpawnerGates[LocationIndex]; 
	const FVector SpawnPoint = SpawnRef->GetSpawnPointVector();

	LocationIndex++;
	
	// Resets the location 
	if(LocationIndex >= SpawnerGates.Num())
	{
		LocationIndex = 0;
	}
	SpawnRef->StartSpawnGateEvent();
	const int EnemyIndex = FMath::RandRange(0, Enemies.Num()-1);
	if(Enemy != nullptr)
	{
		SpawnEnemy(Enemy, SpawnPoint, FRotator(0,0,0));
	}else
	{
		SpawnEnemy(Enemies[EnemyIndex], SpawnPoint, FRotator(0,0,0));
	}
	
	return true;
}




void AEnemy_Spawner::StartNextWave(int Amount)
{
	IncreaseScaling(ScalingValue);
	//AmountOfTotalSquadsToSpawn = AmountOfTotalSquads;
	for(int i = 0; i < Amount; i++)
	{
		if(PlaceEnemiesAtSpawnGates(nullptr))
		{
		}
	}
}

void AEnemy_Spawner::StartNextCustomWave(TSubclassOf<ABaseEnemy> EnemyType, int Amount)
{
	//AmountOfTotalSquadsToSpawn = AmountOfTotalSquads;
	for(int i = 0; i < Amount; i++)
	{
		if(PlaceEnemiesAtSpawnGates(EnemyType))
		{
		}
	}
}

/*
void AEnemy_Spawner::OnDeathEvent()
{
	if(EnemiesToKill > AmountOfEnemiesSpawned)
	{
		if(PlaceEnemiesAtSpawnGates(nullptr))
		{
			AmountOfEnemiesSpawned++;
		}
	}
	
	AmountOfEnemiesKilled++;
	if(AmountOfEnemiesKilled >= EnemiesToKill)
	{
		//Endgame with player as winner
		Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this))->EndGame(true);
	}
}
*/
void AEnemy_Spawner::GetSpawnGatesInScene()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnerGate::StaticClass(), FoundActors);

	for( AActor* Actor : FoundActors)
	{
		if(ASpawnerGate* SpawnerGate = Cast<ASpawnerGate>(Actor))
		{
			SpawnerGates.Add(SpawnerGate);
		}
	}
	
	Algo::RandomShuffle(SpawnerGates);
	for(ASpawnerGate* spawner : SpawnerGates)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *spawner->GetName());
	}
}

// Called every frame
void AEnemy_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

