// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooler.h"

#include "Poolable.h"



void UObjectPooler::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation,
	AActor*& SpawnedActor)
{
	SpawnedActor = SpawnFromPool<AActor>(PoolClass, Location, Rotation);
}

void UObjectPooler::ReturnToPool(AActor* ReturnedActor)
{
	if(ReturnedActor == nullptr)
	{
		return;
	}
	
	const UClass* PoolableClass = ReturnedActor->GetClass();
	
	if(PoolableClass->ImplementsInterface(UPoolable::StaticClass()))
	{
		IPoolable::Execute_ReturnToPool(ReturnedActor);
		FPoolArray* ObjectPool = ObjectPools.Find(PoolableClass);
		if(ObjectPool)
		{
			ObjectPool->Add(ReturnedActor);
		}
	}else
	{
		ReturnedActor->Destroy();
	}
}
