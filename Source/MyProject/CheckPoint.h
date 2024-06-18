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

	UFUNCTION(BlueprintNativeEvent)
	void RespawnPointDisabled();

	UFUNCTION(BlueprintCallable)
	void StartRespawnPointDisabledEvent(); 

	UFUNCTION(BlueprintNativeEvent)
	void RespawnPointSet();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;
	
	UPROPERTY(EditDefaultsOnly)
	bool CanBeReactivated = false; 

	UFUNCTION(BlueprintCallable)
	FString GetAmountCheckPointsAsText() const; 
	
	UFUNCTION()
	void SetIsEnabled(const bool Enabled);
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACheckPointKillBox* RespawnManager;

	UFUNCTION(BlueprintCallable)
	int GetAmountOfCheckPoints() const;

	UFUNCTION(BlueprintCallable)
	bool HasCheckedAllPoints() const;

	UFUNCTION(BlueprintCallable)
	bool HaveIAlreadyBeenActivated();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool HasBeenActivatedBefore = false; 
	
private:
	bool HasBeenActivated = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	FVector GetSpawnPointLocation() const;
	UFUNCTION()
	FRotator GetSpawnerRotator() const; 
	
};
