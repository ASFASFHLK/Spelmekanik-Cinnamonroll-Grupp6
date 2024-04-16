// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_PartnerLocation.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTService_PartnerLocation : public UBTService
{
	GENERATED_BODY()
	UBTService_PartnerLocation();
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
