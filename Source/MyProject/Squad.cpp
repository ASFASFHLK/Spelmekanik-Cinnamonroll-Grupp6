// Fill out your copyright notice in the Description page of Project Settings.


#include "Squad.h"

#include "BaseEnemy.h"
#include "SquadManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tasks/GameplayTask_SpawnActor.h"



// Called when the game starts or when spawned
void ASquad::BeginPlay()
{
	Super::BeginPlay();
	if(RandomlyGenerated)
	{
		CreateRandomSquadMembers();
	}else
	{
		CreateSpecifiedSquadMembers();
	}
}



// Called every frame
void ASquad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASquad::CreateRandomSquadMembers()
{
	while(SquadValue > 0)
	{
		const int32 NextToSpawn = UKismetMathLibrary::RandomIntegerInRange(0, EnemyTypes.Num()-1);
		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemyTypes[NextToSpawn],
			GetActorLocation(), FRotator(), FActorSpawnParameters());
		
		if(SpawnedEnemy == nullptr)
		{
			return;
		}
		SpawnedEnemy->SpawnDefaultController();
		SpawnedEnemy->SetSquad(this);
		SquadMembers.Add(SpawnedEnemy);
		SquadValue--;
	}
}

void ASquad::CreateSpecifiedSquadMembers()
{
	for(int i = 0; i < NumberOfExplosive; i++)
	{
		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemyTypes[0],
			GetActorLocation(), FRotator(), FActorSpawnParameters());
		
		if(SpawnedEnemy == nullptr)
		{
			return;
		}
		SpawnedEnemy->SpawnDefaultController();
		SpawnedEnemy->SetSquad(this);
		SquadMembers.Add(SpawnedEnemy);
		SquadValue--;
	}

	for(int i = 0; i < NumberOfMelee; i++)
	{
		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(EnemyTypes[1],
			GetActorLocation(), FRotator(), FActorSpawnParameters());
		
		if(SpawnedEnemy == nullptr)
		{
			return;
		}
		SpawnedEnemy->SpawnDefaultController();
		SpawnedEnemy->SetSquad(this);
		SquadMembers.Add(SpawnedEnemy);
		SquadValue--;
	}
}

/*
void ASquad::BindAllSquadMembers()
{
	for(ABaseEnemy* Enemy : SquadMembers)
	{
		if(!Enemy->HasPartner())
		{
			if(MemberWithoutPartner != nullptr)
			{
				BindPartners(Enemy,MemberWithoutPartner);
				MemberWithoutPartner = nullptr;
			}else
			{
				MemberWithoutPartner = Enemy;
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
	if(MemberWithoutPartner && MemberWithoutPartner != EnemyToFindPartnerFor)
	{
		if(!SquadMembers.Contains(EnemyToFindPartnerFor)){
			SquadMembers.Add(EnemyToFindPartnerFor);
			EnemyToFindPartnerFor->SetSquad(this);
		}
		BindPartners(MemberWithoutPartner,EnemyToFindPartnerFor);
		MemberWithoutPartner = nullptr;
		return true;
	}
	return false;
}

void ASquad::FindNewPartner(ABaseEnemy* Enemy)
{
	if(MySquadManager)
	{
		if(!MySquadManager->AssignNewPartner(Enemy, this))
		{
			MemberWithoutPartner = Enemy;
		}
	}
}
*/

void ASquad::RemoveFromSquad(ABaseEnemy* EnemyToRemove)
{
	SquadMembers.Remove(EnemyToRemove);
	if(SquadMembers.Num() == 0)
	{
		if(MySquadManager)
		{
			MySquadManager->SquadDied(this);
		}
		Destroy();
	}
}



