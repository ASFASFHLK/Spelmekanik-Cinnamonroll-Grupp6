// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointKillBox.generated.h"
class ACheckPoint; 
UCLASS()
class MYPROJECT_API ACheckPointKillBox : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Box")
	class UBoxComponent* BoxComponent;
	
public:	
	// Sets default values for this actor's properties
	ACheckPointKillBox();
	
	UFUNCTION(BlueprintCallable)
	int GetAmountOfCheckPointsInTheLevel() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentRespawnPoint(ACheckPoint* Point);

	UFUNCTION(BlueprintNativeEvent)
	void PlayerRespawning(); 

   UFUNCTION(BlueprintCallable)
	bool CheckIfAllCheckPointsHaveBeenActivated() const; 

	UFUNCTION(BlueprintCallable)
	int GetAmountOfActivatedCheckPoints() const;

	UFUNCTION(BlueprintCallable)
	int GetAmountOfRespawns() const;

	UFUNCTION(BlueprintCallable)
	FString GetRoundsAsText() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<ACheckPoint*> RespawnPoints;
	TArray<ACheckPoint*> ActivatedCheckPoints;

	UPROPERTY()
	APlayerStart* PlayerStart;
	
	UPROPERTY()
	ACheckPoint* RespawnPoint;
	
	void GetAllRespawnPointsInTheScene();
	
	void FindPlayerStart();
	
	int AmountOfRespawns = 0; 
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
