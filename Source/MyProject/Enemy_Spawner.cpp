// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Spawner.h"

#include "BaseEnemy.h"

// Sets default values
AEnemy_Spawner::AEnemy_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy_Spawner::BeginPlay()
{
	Super::BeginPlay();
	//ABaseEnemy::OnDeath.AddDynamic(this, &AEnemy_Spawner::SpawnEnemy);

	SpawnEnemy();
	AmountOfEnemiesSpawned++;
	
}

void AEnemy_Spawner::SpawnEnemy()
{
	
	if(EnemyTypeOne == nullptr)
	{
		return;
	}
	FActorSpawnParameters SpawnParams;
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	ABaseEnemy* Enemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemyTypeOne, SpawnLocation, Rotation, SpawnParams);

	if(Enemy)
	{
		UE_LOG(LogTemp, Display, TEXT("I have been Spawned"));
		Enemy->OnDeath.BindUFunction(this, TEXT("OnDeathEvent")); 
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("I have not been  Spawned"));
	}
	

}

void AEnemy_Spawner::OnDeathEvent()
{
	UE_LOG(LogTemp, Display, TEXT("I have been called"));
	if(EnemiesToKill >= AmountOfEnemiesSpawned)
	{
		SpawnEnemy();
		AmountOfEnemiesSpawned++;
	}
	AmountOfEnemiesKilled++;
	
	if(AmountOfEnemiesKilled >= EnemiesToKill)
	{
		// call game mode end
	}
}

// Called every frame
void AEnemy_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

