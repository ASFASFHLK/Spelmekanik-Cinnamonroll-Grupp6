// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PartnerInPosition.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "ExplosiveEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_PartnerInPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	AExplosiveEnemy* Enemy = Cast<AExplosiveEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if(MyBlackBoardComponent)
	{
		MyBlackBoardComponent->SetValueAsBool("InPosition",Enemy->BothInPosition());
	}
}
