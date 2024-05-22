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

	virtual void ResetEnemy() override;
	
	UPROPERTY()
	bool PartnerInPosition;

	UFUNCTION()
	bool GetExploded() const {return Exploded;}
	
	
	UFUNCTION()
	bool CanBeThrown();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Explode();

	UFUNCTION(BlueprintCallable)
	float GetExplosionRadius() const {return ExplosionRadius;}

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetIsBeingThrown(bool Value);

private:
	
	UFUNCTION()
	virtual void Attack() override;

	UPROPERTY()
	bool DoingAttack;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionRadius;

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess = true))
	bool Exploded;
};
