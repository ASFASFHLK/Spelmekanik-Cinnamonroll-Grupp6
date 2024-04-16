// Fill out your copyright notice in the Description page of Project Settings.


#include "SquadManager.h"

#include "AsyncTreeDifferences.h"
#include "Squad.h"

// Sets default values
ASquadManager::ASquadManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASquadManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnSquads();
	
}

// Called every frame
void ASquadManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquadManager::AssignNewPartner(ABaseEnemy* EnemyToAssign, ASquad* OriginalSquad)
{
	if(OriginalSquad->FindSquadMemberToBind(EnemyToAssign))
	{
		return;
	}
	
	for(ASquad* Squad : MySquads)
	{
		if(Squad->FindSquadMemberToBind(EnemyToAssign))
		{
			OriginalSquad->RemoveFromSquad(EnemyToAssign);
			break;
		}
	}
}

void ASquadManager::SpawnSquads()
{
	for(int i = 0; i < NumberOfSquads; i++)
	{
		ASquad* SpawnedSquad = GetWorld()->SpawnActor<ASquad>(SquadType,
			GetActorLocation(), FRotator(), FActorSpawnParameters());
		MySquads.Add(SpawnedSquad);
		SpawnedSquad->SetSquadManager(this);
	}
}

