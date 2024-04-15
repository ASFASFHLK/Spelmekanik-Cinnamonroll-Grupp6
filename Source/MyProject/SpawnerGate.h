// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerGate.generated.h"

UCLASS()
class MYPROJECT_API ASpawnerGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerGate();
	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* SpawnGate;

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* SpawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetSpawnPointVector() const;

};
