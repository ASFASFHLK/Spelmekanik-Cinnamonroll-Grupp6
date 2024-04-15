// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad.h"

#include "BaseEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tasks/GameplayTask_SpawnActor.h"

// Sets default values
ASquad::ASquad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASquad::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ASquad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquad::CreateMembers()
{
	int32 Next;
	while(SquadValue >= 0)
	{
		Next = UKismetMathLibrary::RandomIntegerInRange(0, EnemyTypes.Num()-1);
		
		
		FVector SpawnLocation = FVector::ZeroVector; // Set your desired spawn location
		FRotator SpawnRotation = FRotator::ZeroRotator; // Set your desired spawn rotation
		ABaseEnemy* SpawnedActor = GetWorld()->SpawnActor<ABaseEnemy>(EnemyTypes[Next], SpawnLocation, SpawnRotation);
	}
}

