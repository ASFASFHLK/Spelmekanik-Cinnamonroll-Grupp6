// Fill out your copyright notice in the Description page of Project Settings.


#include "SquadManager.h"

#include "DefaultGamemode.h"
#include "Enemy_Spawner.h"
#include "Squad.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASquadManager::ASquadManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASquadManager::BeginPlay()
{
	Super::BeginPlay();
	EnemySpawner = Cast<AEnemy_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy_Spawner::StaticClass()));
}

// Called every frame
void ASquadManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
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
*/

void ASquadManager::SquadDied(ASquad* SquadThatDied)
{
	MySquads.Remove(SquadThatDied);
	//EnemySpawner->SpawnEnemy();
	SquadsThatHaveDied++;
	UE_LOG(LogTemp, Warning, TEXT("A squad has died, totals squads that have died %i"), SquadsThatHaveDied)
	if(SquadsThatHaveDied >= NumbersOfSquadsThatNeedToDie)
	{
		ADefaultGamemode* Gm = Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this));
		if(Gm)
		{
			Gm->EndGame(true);
		}
	}
}

void ASquadManager::AddSquad(ASquad* SquadToAdd)
{
	MySquads.Add(SquadToAdd);
}

void ASquadManager::StartNextWave()
{
	SquadsThatHaveDied = 0;
}


