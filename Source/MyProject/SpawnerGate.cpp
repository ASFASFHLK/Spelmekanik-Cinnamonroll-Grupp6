// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerGate.h"

// Sets default values
ASpawnerGate::ASpawnerGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnGate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Gate"));
	RootComponent = SpawnGate;
	
	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
}

void ASpawnerGate::SpawnGateActivated_Implementation()
{
	
}

void ASpawnerGate::StartSpawnGateEvent()
{
	SpawnGateActivated();
}

// Called when the game starts or when spawned
void ASpawnerGate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnerGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnerGate::GetSpawnPointVector() const
{
	return SpawnPoint->GetComponentLocation();
}

FRotator ASpawnerGate::GetSpawnerRotator() const
{
	return SpawnPoint->GetComponentRotation(); 
}



