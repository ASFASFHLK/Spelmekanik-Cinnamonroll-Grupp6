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

	ABaseEnemy::OnDeath.AddDynamic(this, &AEnemySpawner::OnEnemyDeath);
	
}

// Called every frame
void AEnemy_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

