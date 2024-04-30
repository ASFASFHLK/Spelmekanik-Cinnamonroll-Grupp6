// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DecideToThrowOrSpawn.h"

#include "AIController.h"
#include "MeleeEnemy.h"


EBTNodeResult::Type UBTTask_DecideToThrowOrSpawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackBoardComponent = OwnerComp.GetBlackboardComponent();
	const AAIController* AIController = OwnerComp.GetAIOwner();            
	const AMeleeEnemy* Enemy = Cast<AMeleeEnemy>(AIController->GetPawn());

	;

	
	int ThrowProbability = Enemy->GetThrowDesire();
	
	int SpawnProbability = Enemy->GetSpawnDesire();

	const int TotalDesire = ThrowProbability + SpawnProbability;

	const int RandomNumber = FMath::RandRange(0, TotalDesire);

	if (SpawnProbability < ThrowProbability)
	{
		if(SpawnProbability >= RandomNumber)
		{
			UE_LOG(LogTemp, Warning, TEXT("SPAWNAR"));
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("KASTAR"));
		}
	}
	else
	{
		if(ThrowProbability >= RandomNumber)
		{
			UE_LOG(LogTemp, Warning, TEXT("KASTAR"));
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("SPAWNAR"));
		}
	}
	
	
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
