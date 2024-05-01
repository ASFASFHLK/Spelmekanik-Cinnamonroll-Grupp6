// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SpawnExplosive.generated.h"

class AMeleeEnemy;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTTask_SpawnExplosive : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	AMeleeEnemy* Enemy;
};
