// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LockInPlace.h"

#include "AIController.h"
#include "RangeEnemy.h"

EBTNodeResult::Type UBTTask_LockInPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	Enemy = Cast<ARangeEnemy>(AIController->GetPawn());
	Enemy->LockInPlace();
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
