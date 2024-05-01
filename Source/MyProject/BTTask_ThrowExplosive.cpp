// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ThrowExplosive.h"

#include "AIController.h"
#include "MeleeEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_ThrowExplosive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	Enemy = Cast<AMeleeEnemy>(AIController->GetPawn());
	Enemy->ThrowExplosiveEnemy();
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
