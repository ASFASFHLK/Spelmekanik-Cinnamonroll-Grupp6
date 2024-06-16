// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

class USphereComponent;
class ACheckPointKillBox;

UCLASS()
class MYPROJECT_API ACheckPoint : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACheckPoint();

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* SpawnGate;

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* SpawnPoint;

	void SetRespawnManager( ACheckPointKillBox* Manager);

	UFUNCTION(BlueprintNativeEvent)
	void RespawnEvent();
	
	void StartRespawnSpawnEvent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditDefaultsOnly)
	bool CanBeReactivated = false; 
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	bool HasBeenActivated = false;
	
	UPROPERTY(VisibleAnywhere)
	ACheckPointKillBox* RespawnManager; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	FVector GetSpawnPointLocation() const;
	UFUNCTION()
	FRotator GetSpawnerRotator() const; 
	
};
