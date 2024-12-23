// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DoAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTTask_DoAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
	ABaseEnemy* Enemy;
};
