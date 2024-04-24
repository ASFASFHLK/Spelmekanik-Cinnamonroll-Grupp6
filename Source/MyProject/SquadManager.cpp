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

void ASquadManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASquadManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASquadManager::AssignNewPartner(ABaseEnemy* EnemyToAssign, ASquad* OriginalSquad)
{
	if(OriginalSquad->FindSquadMemberToBind(EnemyToAssign))
	{
		return true;
	}
	
	for(ASquad* Squad : MySquads)
	{
		if(Squad->FindSquadMemberToBind(EnemyToAssign))
		{
			OriginalSquad->RemoveFromSquad(EnemyToAssign);
			return true;
		}
	}
	return false;
}

void ASquadManager::SquadDied(ASquad* SquadThatDied)
{
	MySquads.Remove(SquadThatDied);

	if(MySquads.Num() <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Alla dog"));
	}
}

void ASquadManager::AddSquad(ASquad* SquadToAdd)
{
	MySquads.Add(SquadToAdd);
}


