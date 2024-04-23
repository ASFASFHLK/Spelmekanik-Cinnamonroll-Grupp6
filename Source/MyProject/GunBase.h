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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void Shoot();
private:
	UFUNCTION()
	void ShotGunShot();
	UFUNCTION()
	void UseShotGun();
	UFUNCTION()
	void Reload();
	UPROPERTY()
	FTimerHandle ShootTimerHandle = FTimerHandle();
	UPROPERTY()
	FTimerHandle BurstTimerHandle = FTimerHandle();
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess= true), Category = "Gun")
	USoundBase* ShotSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess= true), Category = "Gameplay")
	FVector MuzzleOffset = FVector(100,0,10);
	UPROPERTY()
	bool bCanShoot = true;
	UPROPERTY()
	bool bCanceledShot = false;
	UPROPERTY()
	float ReloadTime = 0.8f;
	UPROPERTY()
	float BurstTime = 0.3f;
	UPROPERTY(EditAnywhere)
	int Pellets = 20;
	UPROPERTY(EditAnywhere)
	float Damage = 5;
	UPROPERTY()
	int Bursts = 5;
	UPROPERTY()
	int ShotDistance = 800;
	UPROPERTY()
	int BurstCheck = 0;
};
