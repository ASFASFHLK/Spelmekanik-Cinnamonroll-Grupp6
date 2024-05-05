// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPooler.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UObjectPooler : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	AActor* SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	void ReturnToPool(AActor* ReturnedActor);

private:
	UPROPERTY()
	TArray<AActor*> ObjectPool;
};
