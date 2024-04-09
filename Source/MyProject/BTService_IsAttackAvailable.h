// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_IsAttackAvailable.generated.h"

class ABaseEnemy;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTService_IsAttackAvailable : public UBTService
{
	GENERATED_BODY()

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	ABaseEnemy* Enemy;
	
};
