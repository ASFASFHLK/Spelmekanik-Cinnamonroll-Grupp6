// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DetourCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "EnemyAIController.generated.h"

class ABaseEnemy;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController(const FObjectInitializer& ObjectInitializer);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	ABaseEnemy* Enemy;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* AIBehavior;

	
	void SetAvoidanceQuality(ECrowdAvoidanceQuality::Type Quality) const;

};
