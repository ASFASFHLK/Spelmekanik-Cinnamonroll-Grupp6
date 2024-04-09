// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerClose.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_PlayerClose::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);

	//if(UE::Geometry::Distance(Player->GetActorLocation(),OwnerComp.GetAIOwner()->GetActorLocation()))
	
	MyBlackBoardComponent->SetValueAsBool("PlayerIsClose",true);
}
