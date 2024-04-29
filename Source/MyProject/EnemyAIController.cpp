// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
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