// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "AI")
	APawn* CurrentTarget;

	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentTarget() const {return CurrentTarget;}
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* AIBehavior;

};
