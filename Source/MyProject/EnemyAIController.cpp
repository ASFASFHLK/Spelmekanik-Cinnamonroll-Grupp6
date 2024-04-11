// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"


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
	//SetFocus(Enemy->GetCurrentTarget());
}