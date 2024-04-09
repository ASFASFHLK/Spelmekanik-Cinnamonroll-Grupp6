// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DoAttack.h"

#include "BaseEnemy.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"



EBTNodeResult::Type UBTTask_DoAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	Enemy = Cast<ABaseEnemy>(AIController->GetPawn());
	Enemy->Attack();
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
