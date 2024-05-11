// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckIfAirborne.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void UBTService_CheckIfAirborne::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	Enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	bool test = Enemy->GetMovementComponent()->IsFalling();
	UE_LOG(LogTemp, Warning, TEXT("My boolean value is: %s"), (!test ? TEXT("true") : TEXT("false")));
	

	MyBlackBoardComponent->SetValueAsBool("NotAirBorne", !test);
}
