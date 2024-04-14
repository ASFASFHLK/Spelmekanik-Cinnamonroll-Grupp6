// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Spawner.h"
#include "DefaultGamemode.h"
#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnerGate.h"

// Sets default values
AEnemy_Spawner::AEnemy_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEnemy_Spawner::BeginPlay()
{
	Super::BeginPlay();

	GetSpawnGatesInScene();
	
	for(int i = 0; i < AmountToSpawnAtStart; i++)
	{
		SpawnEnemy();
		AmountOfEnemiesSpawned++;
	}
}

void AEnemy_Spawner::SpawnEnemy()
{
	if(Enemies.Num() < 1 or SpawnerGates.Num() < 1) // prevents indexing into invalid arrays 
	{
		return;
	}
	
	const FVector SpawnPoint = SpawnerGates[LocationIndex]->GetSpawnPointVector();
	LocationIndex++;
	
	// Resets the location 
	if(LocationIndex >= SpawnerGates.Num())
	{
		LocationIndex = 0;
	}
	
	const int EnemyIndex = FMath::RandRange(0, Enemies.Num()-1);
	
	ABaseEnemy* Enemy = GetWorld()->SpawnActor<ABaseEnemy>(Enemies[EnemyIndex], SpawnPoint, FRotator(), FActorSpawnParameters());

	if(Enemy)
	{
		UE_LOG(LogTemp, Display, TEXT("I have been Spawned %ls"), *GetName());
		Enemy->OnDeath.BindUFunction(this, TEXT("OnDeathEvent"));
		Enemy->SpawnDefaultController();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("I have not been Spawned %ls"), *GetName());
	}
}

void AEnemy_Spawner::OnDeathEvent()
{
	UE_LOG(LogTemp, Display, TEXT("I have been called"));
	if(EnemiesToKill > AmountOfEnemiesSpawned)
	{
		SpawnEnemy();
		AmountOfEnemiesSpawned++;
	}
	
	AmountOfEnemiesKilled++;
	
	if(AmountOfEnemiesKilled >= EnemiesToKill)
	{
		//Endgame with player as winner
		Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this))->EndGame(true);
		
	}
}

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
}

// Called every frame
void AEnemy_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

