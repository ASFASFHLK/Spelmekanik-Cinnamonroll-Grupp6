// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad.h"

#include "BaseEnemy.h"
#include "DefaultGamemode.h"
#include "Enemy_Spawner.h"
#include "ExplosiveEnemy.h"
#include "NetworkMessage.h"
#include "SquadManager.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tasks/GameplayTask_SpawnActor.h"



// Called when the game starts or when spawned
void ASquad::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = UGameplayStatics::GetPlayerPawn(this, 0);
	EnemySpawner = Cast<AEnemy_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy_Spawner::StaticClass()));
	GameMode = Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this));
}

ASquad::ASquad()
{
	PrimaryActorTick.bCanEverTick = true;
}


// Called every frame
void ASquad::Tick(float DeltaTime)
{
	
	if(!PlayerCharacter->GetMovementComponent()->IsFalling())
	{
		PlayerLocation = PlayerCharacter->GetActorLocation();
	}else
	{
		PlayerLocation.X = PlayerCharacter->GetActorLocation().X;
		PlayerLocation.Y = PlayerCharacter->GetActorLocation().Y;
	}
	Super::Tick(DeltaTime);
}

void ASquad::RemoveFromSquad(ABaseEnemy* EnemyToRemove)
{
	AExplosiveEnemy* ExplosiveEnemy = Cast<AExplosiveEnemy>(EnemyToRemove);
	if(ExplosiveEnemy)
	{
		ExplosiveEnemies.Remove(ExplosiveEnemy);
		if(GameMode->GetTutorial() && GameMode->GetTutorialStep() == 2)
		{
			GameMode->OnEnemyKilled();
		}
		if(!ExplosiveEnemy->GetExploded())
		{
			GameMode->IncreaseEnemiesKilled();
		}
		
	}else
	{
		SquadMembers.Remove(EnemyToRemove);
		GameMode->OnEnemyKilled();
		GameMode->IncreaseEnemiesKilled();
	}
}

void ASquad::ExplodeAllEnemies()
{
	for(int i = 0; i < ExplosiveEnemies.Num(); i++)
	{
		ExplosiveEnemies[i]->Explode();
		ExplosiveEnemies[i]->ShutDownBehavior();
	}
	for(int i = 0; i < SquadMembers.Num(); i++)
	{
		SquadMembers[i]->Ragdoll();
		SquadMembers.Remove(SquadMembers[i]);
		
	}
}

void ASquad::AddExplosiveToSquad(AExplosiveEnemy* EnemyToAdd)
{
	if(EnemyToAdd)
	{
		ExplosiveEnemies.Add(EnemyToAdd);
		EnemyToAdd->SetSquad(this);
	}
}

void ASquad::AddMemberToASquad(ABaseEnemy* EnemyToAdd)
{
	if(EnemyToAdd)
	{
		if(EnemyToAdd->IsA(AExplosiveEnemy::StaticClass()))
		{
			ExplosiveEnemies.Add(Cast<AExplosiveEnemy>(EnemyToAdd));
		}else
		{
			SquadMembers.Add(EnemyToAdd);
		}
		EnemyToAdd->SetSquad(this);
	}
}

void ASquad::ShutDownAllEnemies()
{
	for(int i = 0; i < SquadMembers.Num(); i++)
	{
		SquadMembers[i]->ShutDownBehavior();
	}
	for(int i = 0; i < ExplosiveEnemies.Num(); i++)
	{
		ExplosiveEnemies[i]->ShutDownBehavior();
	}
}

AExplosiveEnemy* ASquad::LookForExplosiveToThrow()
{
	AExplosiveEnemy* ClosestEnemy = nullptr;
	float ClosestRange = 1000000;
	for(int i = 0; i < ExplosiveEnemies.Num(); i++)
	{
		AExplosiveEnemy* NextEnemy = ExplosiveEnemies[i];
		const float Next = FVector::Distance(NextEnemy->GetActorLocation(), PlayerLocation);
		
		if(Next < ClosestRange && NextEnemy->CanBeThrown())
		{
			ClosestRange = Next;
			ClosestEnemy = ExplosiveEnemies[i];
		}
	}
	return ClosestEnemy; 
}

bool ASquad::CanSpawnExplosive()
{
	if(ExplosiveEnemies.Num() < NumberOfExplosivesAllowed)
	{
		return true;
	}
	return false;
}




