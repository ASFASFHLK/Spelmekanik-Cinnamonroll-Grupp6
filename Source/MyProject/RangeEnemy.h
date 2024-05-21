// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "RangedEnemyProjectile.h"
#include "RangeEnemy.generated.h"


UCLASS()
class MYPROJECT_API ARangeEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ARangeEnemy();

	UFUNCTION(BlueprintNativeEvent)
	void Flee();
	
	UFUNCTION(BlueprintNativeEvent)
	void LockInPlace();

	UFUNCTION(BlueprintNativeEvent)
	void FireProjectile();

private:
	virtual void Attack() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ARangedEnemyProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	USceneComponent* ProjectileSpawnPoint;
	
};

