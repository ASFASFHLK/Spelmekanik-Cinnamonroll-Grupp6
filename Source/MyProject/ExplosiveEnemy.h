// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "ExplosiveEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AExplosiveEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	
	bool BothInPosition();
	
	UPROPERTY()
	bool PartnerInPosition;

	UPROPERTY()
	bool IAmInPosition;

	UFUNCTION()
	bool CanBeThrown();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Explode();

	UFUNCTION(BlueprintCallable)
	float GetExplosionRadius() const {return ExplosionRadius;}

private:
	
	UFUNCTION()
	virtual void Attack() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionRadius;
};
