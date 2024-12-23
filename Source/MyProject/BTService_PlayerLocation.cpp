// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_PlayerLocation.h"

#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Kismet/GameplayStatics.h"



UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("LocationofPlayerUpdate");
	
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	const AAIController* AIController = OwnerComp.GetAIOwner();            
	const ABaseEnemy* Enemy = Cast<ABaseEnemy>(AIController->GetPawn());

	if(MyBlackBoardComponent)
	{
		MyBlackBoardComponent->SetValueAsVector("PlayerLocation", Enemy->GetPlayerLocationFromSquad());
	}
}
