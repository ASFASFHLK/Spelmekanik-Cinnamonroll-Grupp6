// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnExplosive.h"

#include "AIController.h"
#include "MeleeEnemy.h"

EBTNodeResult::Type UBTTask_SpawnExplosive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	Enemy = Cast<AMeleeEnemy>(AIController->GetPawn());
	Enemy->SpawnExplosiveEnemy();
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
