// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "BaseEnemy.h"
#include "Tasks/GameplayTask_SpawnActor.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<ABaseEnemy> EnemyToSpawn)
{
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ABaseEnemy>(EnemyToSpawn, GetActorLocation(), GetActorRotation(), SpawnInfo);
}


// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	

}

