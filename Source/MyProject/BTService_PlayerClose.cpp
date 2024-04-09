// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerClose.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_PlayerClose::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	float Value = UE::Geometry::Distance(Player->GetActorLocation(),Enemy->GetActorLocation());

	MyBlackBoardComponent->SetValueAsBool("PlayerIsClose",Value < Enemy->GetTargetIsCloseRange());
}
