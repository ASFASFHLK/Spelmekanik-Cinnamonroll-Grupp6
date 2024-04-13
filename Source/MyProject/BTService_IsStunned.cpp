// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsStunned.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

class ABaseEnemy;

void UBTService_IsStunned::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	//MyBlackBoardComponent->SetValueAsBool("IsStunned", Enemy->GetIsStunned());
}
