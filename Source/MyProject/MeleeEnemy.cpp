// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"

#include "EnemyAIController.h"
#include "ExplosiveEnemy.h"
#include "KismetTraceUtils.h"
#include "Squad.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"


void AMeleeEnemy::ThrowExplosiveEnemy_Implementation()
{
	
}

void AMeleeEnemy::SetCanThrow_Implementation(const bool Value)
{
	if(MyBlackBoard)
	{
		MyBlackBoard->SetValueAsBool("CanThrowOrSpawn", Value);
	}
}

void AMeleeEnemy::CallExplosiveToMove()
{
	if(MySquad)
	{
		EnemyToThrow = MySquad->LookForExplosiveToThrow();
	}
	
	if(EnemyToThrow)
	{
		AAIController* EnemyToThrowController = Cast<AEnemyAIController>(EnemyToThrow->GetController());
		EnemyToThrowController->GetBlackboardComponent()->SetValueAsBool("MoveToPartner", true);
		EnemyToThrow->SetPartner(this);
		SetPartner(EnemyToThrow);
	}else
	{
		SpawnExplosiveEnemy();
	}
	ResetThrowTimer();
}

void AMeleeEnemy::ResetThrowTimer()
{
	CurrentThrowOrSpawnTimer = ThrowOrSpawnTimer;
	SetCanThrow(false);
}

void AMeleeEnemy::SpawnExplosiveEnemy_Implementation()
{
}


void AMeleeEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	CurrentThrowOrSpawnTimer -= DeltaSeconds;
	if(CurrentThrowOrSpawnTimer <= 0)
	{
		SetCanThrow(true);
	}
}

void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
	DecideWhichType();
	CurrentThrowOrSpawnTimer = 0;
}


void AMeleeEnemy::Attack()
{
	Super::Attack();
	if(bIsParried)
	{
		return;
	}
	const FVector End = (GetActorForwardVector() * 100) + GetActorLocation();
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	
	
	UKismetSystemLibrary::SphereTraceSingle(this,GetActorLocation(),End,50,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),false,ActorsToIgnore, EDrawDebugTrace::ForDuration,HitResult,true,
		FColor::Red, FColor::Green, 1.5f);

	if(ABaseCharacter* ActorHit = Cast<ABaseCharacter>(HitResult.GetActor()))
	{
		ActorHit->TakeDamage(DamageDealt, FDamageEvent(), GetController(), this);

	}
}

//
//	Gives the actor a certain type of enemy they are based on the values given
//
void AMeleeEnemy::DecideWhichType()
{
	SpawnerValue = FMath::RandRange(0, 10);
	ThrowerValue = FMath::RandRange(0, 10);
	
	if(SpawnerValue + ThrowerValue < 8)
	{
		GorillaType = "Charger";
		GorillaTypeInt = 0;
		
	}else if(ThrowerValue - SpawnerValue > 2)
	{
		GorillaType = "Thrower";
		GorillaTypeInt = 1;
		
	}else if(SpawnerValue - ThrowerValue > 2)
	{
		GorillaType = "Spawner";
		GorillaTypeInt = 2;
		
	}else
	{
		GorillaTypeInt = FMath::RandRange(1,2);
	}

	/*else
	{
		GorillaType = "Balanced";
		GorillaTypeInt = 3;
	}
	*/

	MyBlackBoard->SetValueAsInt("GorillaType", GorillaTypeInt);
}
