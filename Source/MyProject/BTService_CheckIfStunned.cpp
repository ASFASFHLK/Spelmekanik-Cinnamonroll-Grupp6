// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckIfStunned.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckIfStunned::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	Enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());

}
