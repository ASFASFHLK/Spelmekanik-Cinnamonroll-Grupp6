// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS(BlueprintType)
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
	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintCallable)
	void CancelShot();
	UFUNCTION(BlueprintCallable)
	void RifleShot();
	UFUNCTION(BlueprintCallable)
	void ShotGunShot();
	UFUNCTION(BlueprintCallable)
	void LaserShot();
	UFUNCTION(BlueprintCallable)
	void ReloadShotGunShot();
	UFUNCTION(BlueprintCallable)
	void ReloadPunch();
	UFUNCTION(BlueprintCallable)
    void ChangeGunType();
	UFUNCTION(BlueprintCallable)
    void Punch();
private:
	UFUNCTION()
	void UseShotGun();
	UFUNCTION()
	void Reload();
	UPROPERTY()
	FTimerHandle ShootTimerHandle = FTimerHandle();
	UPROPERTY()
	FTimerHandle BurstTimerHandle = FTimerHandle();
	UPROPERTY()
	FTimerHandle HitTimerHandle = FTimerHandle();
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess= true), Category = "Gun")
	USoundBase* ShotSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess= true), Category = "Gun")
	FVector MuzzleOffset = FVector(100,0,10);
	UPROPERTY()
	bool bCanShoot = true;
	UPROPERTY()
    bool bRifleShouldShoot = true;
	UPROPERTY()
	bool bCanceledShot = false;
	UPROPERTY()
	bool bCanHit = true;
	UPROPERTY()
	float ReloadTime = 0.8f;
	UPROPERTY()
	float BurstTime = 0.3f;
	UPROPERTY(EditAnywhere)
	int Pellets = 20;
	UPROPERTY(EditAnywhere)
	int PunchRadius = 100;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	int GunType = 0;
	UPROPERTY(EditAnywhere)
	float Damage = 5;
	UPROPERTY()
	int Bursts = 5;
	UPROPERTY(EditAnywhere)
	int LaunchDistance = 5000;
	UPROPERTY()
	int ShotGunReloadTime = 1;
	UPROPERTY()
	int ShotDistance = 800;
	UPROPERTY()
	int PunchDistance = 100;
	UPROPERTY()
	int BurstCheck = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	float RifleShotCooldown;
	UPROPERTY()
	float CurrentRifleShotCooldown;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	FRotator SpawnRotation;
	UPROPERTY()
	FVector SpawnLocation;
	FCollisionQueryParams QueryParams = FCollisionQueryParams();
	UPROPERTY()
	UWorld* const World = GetWorld();
 };
