// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Poolable.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPooler.generated.h"

USTRUCT()
struct FPoolArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> ObjectPool;

	bool IsEmpty() const
	{
		return ObjectPool.IsEmpty();
	}

	AActor* Pop()
	{
		return ObjectPool.Pop();
	}

	void Add(AActor* ActorToAdd)
	{
		ObjectPool.Add(ActorToAdd);
	}
	
};
UCLASS()
class MYPROJECT_API UObjectPooler : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "PoolClass", DynamicOutputParam = "SpawnedActor"))
	void SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation, AActor*& SpawnedActor);

	template<typename T>
	T* SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation);
	
	UFUNCTION(BlueprintCallable)
	void ReturnToPool(AActor* ReturnedActor);

private:
	UPROPERTY()
	TMap<UClass*, FPoolArray> ObjectPools;
};

template <typename T>
T* UObjectPooler::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation)
{
	
	T* ActorToBeSpawned = nullptr;
	if(PoolClass.Get()->ImplementsInterface(UPoolable::StaticClass()))
	{
		FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
		
		if(ObjectPool.IsEmpty())
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			ActorToBeSpawned = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParameters);
			
		}else
		{
			ActorToBeSpawned = CastChecked<T>(ObjectPool.Pop());
			ActorToBeSpawned->SetActorLocationAndRotation(Location, Rotation);
			IPoolable::Execute_SpawnFromPool(ActorToBeSpawned);
		}
		
	}
	return ActorToBeSpawned;
}
