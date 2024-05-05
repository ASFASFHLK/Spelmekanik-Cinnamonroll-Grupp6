// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include <strmif.h>

#include "Navigation/CrowdFollowingComponent.h"
#include "BaseEnemy.h"


class UCrowdFollowingComponent;

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)

		:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>
		(TEXT("PathFollowingComponent")))
{
	
}


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	//SetAvoidanceQuality(ECrowdAvoidanceQuality::High);
	
	Enemy = Cast<ABaseEnemy>(GetPawn());
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyAIController::SetAvoidanceQuality(const ECrowdAvoidanceQuality::Type Quality) const
{
	if (UCrowdFollowingComponent* Pathfol = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Pathfol->SetCrowdAvoidanceQuality(Quality);
		Pathfol->SetCrowdObstacleAvoidance(true,true);
		Pathfol->SetCrowdSeparationWeight(1, true);
		Pathfol->SetCrowdSeparation(true, true);
	}
}
