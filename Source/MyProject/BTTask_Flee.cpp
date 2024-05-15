// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Flee.h"

#include "AIController.h"
#include "RangeEnemy.h"

EBTNodeResult::Type UBTTask_Flee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	Enemy = Cast<ARangeEnemy>(AIController->GetPawn());
	Enemy->Flee();
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
