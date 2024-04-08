// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class MYPROJECT_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();
	bool Fire(); // returns true if it hit something 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	UMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere, Category="Settings")
	int32 Damage = 10;
	UPROPERTY(EditAnywhere,Category="Settings")
	float FireRate = 10;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
