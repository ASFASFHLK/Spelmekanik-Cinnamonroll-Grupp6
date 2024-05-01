// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PartnerLocation.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PartnerLocation::UBTService_PartnerLocation()
{
	NodeName = "Partner Location";
}

void UBTService_PartnerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	
	ABaseEnemy* Partner = Enemy->GetPartner();

	if(MyBlackBoardComponent && Partner)
	{
		if(Partner)
		{
			MyBlackBoardComponent->SetValueAsVector("PartnerLocation",Partner->GetActorLocation());
			MyBlackBoardComponent->SetValueAsBool("HasPartner",true);
		
			if(Partner->IsA(ARangeEnemy::StaticClass()))
			{
				MyBlackBoardComponent->SetValueAsObject("RangedPartner",Partner);
			}
			else if(Partner->IsA(AMeleeEnemy::StaticClass()))
			{
				MyBlackBoardComponent->SetValueAsObject("MeleePartner",Partner);
			}else
			{
				MyBlackBoardComponent->SetValueAsObject("ExplosivePartner",Partner);
			}
		}else
		{
			MyBlackBoardComponent->SetValueAsBool("HasPartner",false);
		}
	}
}
