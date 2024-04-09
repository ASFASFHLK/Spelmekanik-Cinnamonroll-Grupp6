// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
	}
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(AIBehavior != nullptr)
	{
	}
}