// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad.h"

#include "BaseEnemy.h"
#include "SquadManager.h"
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
	CreateSquadMembers();
	BindAllSquadMembers();
	
}

// Called every frame
void ASquad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquad::CreateSquadMembers()
{
	while(SquadValue > 0)
	{
		const int32 NextToSpawn = UKismetMathLibrary::RandomIntegerInRange(0, EnemyTypes.Num()-1);
		
		
		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemyTypes[NextToSpawn],
			GetActorLocation(), FRotator(), FActorSpawnParameters());
		if(SpawnedEnemy == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Null"));
			return;
		}
		SpawnedEnemy->SpawnDefaultController();
		SpawnedEnemy->SetSquad(this);
		SquadMembers.Add(SpawnedEnemy);
		SquadValue--;
	}
}

void ASquad::BindAllSquadMembers()
{
	ABaseEnemy* PreviousEnemy = nullptr;
	for(ABaseEnemy* Enemy : SquadMembers)
	{
		if(!Enemy->HasPartner())
		{
			if(PreviousEnemy != nullptr)
			{
				BindPartners(Enemy,PreviousEnemy);
				PreviousEnemy = nullptr;
			}else
			{
				PreviousEnemy = Enemy;
			}
		}
	}
}

void ASquad::BindPartners(ABaseEnemy* EnemyOne, ABaseEnemy* EnemyTwo)
{
	EnemyOne->SetPartner(EnemyTwo);
	EnemyTwo->SetPartner(EnemyOne);
}

bool ASquad::FindSquadMemberToBind(ABaseEnemy* EnemyToFindPartnerFor)
{
	for(ABaseEnemy* Enemy : SquadMembers)
	{
		if(!Enemy->HasPartner() && Enemy != EnemyToFindPartnerFor)
		{
			if(!SquadMembers.Contains(EnemyToFindPartnerFor)){
				SquadMembers.Add(EnemyToFindPartnerFor);
			}
			BindPartners(Enemy,EnemyToFindPartnerFor);
			EnemyToFindPartnerFor->SetSquad(this);
			return true;
		}
	}
	return false;
}

void ASquad::FindNewPartner(ABaseEnemy* Enemy)
{
	if(MySquadManager)
	{
		MySquadManager->AssignNewPartner(Enemy, this);
	}
}

void ASquad::RemoveFromSquad(ABaseEnemy* EnemyToRemove)
{
	SquadMembers.Remove(EnemyToRemove);
	if(SquadMembers.Num() == 0)
	{
		Destroy();
	}
}



