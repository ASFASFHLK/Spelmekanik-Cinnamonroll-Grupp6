// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooler.h"

#include "Poolable.h"

AActor* UObjectPooler::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation)
{
	AActor* ActorToBeSpawned = nullptr;
	if(PoolClass.Get()->ImplementsInterface(UPoolable::StaticClass()))
	{
		if(ObjectPool.IsEmpty())
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorToBeSpawned = GetWorld()->SpawnActor<AActor>(PoolClass, Location, Rotation, SpawnParameters);
			
		}else
		{
			ActorToBeSpawned = ObjectPool.Pop();
			ActorToBeSpawned->SetActorLocationAndRotation(Location, Rotation);
			IPoolable::Execute_SpawnFromPool(ActorToBeSpawned);
		}
		
	}
	return ActorToBeSpawned;
}

void UObjectPooler::ReturnToPool(AActor* ReturnedActor)
{
	if(ReturnedActor == nullptr)
	{
		return;
	}
	if(ReturnedActor->GetClass()->ImplementsInterface(UPoolable::StaticClass()))
	{
		IPoolable::Execute_ReturnToPool(ReturnedActor);
		ObjectPool.Add(ReturnedActor);
	}else
	{
		ReturnedActor->Destroy();
	}
}
