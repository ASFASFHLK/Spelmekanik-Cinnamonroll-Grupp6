// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ExplosiveInPosition.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "ExplosiveEnemy.h"

EBTNodeResult::Type UBTTask_ExplosiveInPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	Enemy = Cast<AExplosiveEnemy>(AIController->GetPawn());
	AExplosiveEnemy* EnemyPartner = Cast<AExplosiveEnemy>(Enemy->GetPartner());
	Enemy->IAmInPosition = true;
	EnemyPartner->PartnerInPosition = true;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
