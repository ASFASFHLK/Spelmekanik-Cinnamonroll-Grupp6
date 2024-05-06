// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Spawner.h"
#include "DefaultGamemode.h"
#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnerGate.h"
#include "SquadManager.h"

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
	//SquadManager = Cast<ASquadManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquadManager::StaticClass()));
	Squad = Cast<ASquad>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquad::StaticClass()));
	
	StartNextWave();
}


bool AEnemy_Spawner::PlaceEnemiesAtSpawnGates()
{
	if(Enemies.Num() < 1 or SpawnerGates.Num() < 1) // prevents indexing into invalid arrays 
	{
		return false;
	}
	
/*
	if(AmountOfTotalSquadsToSpawn <= 0)
	{
		return;
	}
	

	if(SpawnerGates.Num() < 1) // prevents indexing into invalid arrays 
	{
		return;
	}
	*/
	
	const FVector SpawnPoint = SpawnerGates[LocationIndex]->GetSpawnPointVector();
	LocationIndex++;
	
	// Resets the location 
	if(LocationIndex >= SpawnerGates.Num())
	{
		LocationIndex = 0;
	}
/*
	if(ASquad* Squad = GetWorld()->SpawnActor<ASquad>(SquadType, SpawnPoint, FRotator(),FActorSpawnParameters()))
	{
		Squad->SetSquadManager(SquadManager);
		SquadManager->AddSquad(Squad);
	}
	*/

	
	
	const int EnemyIndex = FMath::RandRange(0, Enemies.Num()-1);
	
	SpawnEnemy(Enemies[EnemyIndex], SpawnPoint, FRotator(0,0,0));
	/*
	if(ABaseEnemy* Enemy = Test(Enemies[EnemyIndex], SpawnPoint, FRotator()))
	{
		Enemy->OnDeath.BindUFunction(this, TEXT("OnDeathEvent"));
		Squad->AddToSquad(Enemy);
		return true;
	}
	*/
	return true;
}




void AEnemy_Spawner::StartNextWave()
{
	AmountOfEnemiesKilled = 0;
	AmountOfEnemiesSpawned = 0;
	//AmountOfTotalSquadsToSpawn = AmountOfTotalSquads;
	for(int i = 0; i < AmountToSpawnAtStart; i++)
	{
		if(PlaceEnemiesAtSpawnGates())
		{
			AmountOfEnemiesSpawned++;
		}
	}
}



void AEnemy_Spawner::OnDeathEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("SPAWNING NEW ENEMY"));
	if(EnemiesToKill > AmountOfEnemiesSpawned)
	{
		if(PlaceEnemiesAtSpawnGates())
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

