// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CallPartnerToMove.h"

#include "AIController.h"
#include "MeleeEnemy.h"

EBTNodeResult::Type UBTTask_CallPartnerToMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	Enemy = Cast<AMeleeEnemy>(AIController->GetPawn());
	Enemy->CallExplosiveToMove();
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
