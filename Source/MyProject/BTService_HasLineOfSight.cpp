// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_HasLineOfSight.h"
#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_HasLineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	Enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	MyBlackBoardComponent->SetValueAsBool("HasLineOfSight", OwnerComp.GetAIOwner()->LineOfSightTo(Enemy->GetCurrentTarget()));
}