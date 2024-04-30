// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WhichType.h"

#include "AIController.h"
#include "MeleeEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_WhichType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	const AAIController* AIController = OwnerComp.GetAIOwner();
	const AMeleeEnemy* Enemy = Cast<AMeleeEnemy>(AIController->GetPawn());
	 
	
	if(MyBlackBoardComponent)
	{
		MyBlackBoardComponent->SetValueAsInt("GorillaType", Enemy->GetGorillaType());
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}


	
