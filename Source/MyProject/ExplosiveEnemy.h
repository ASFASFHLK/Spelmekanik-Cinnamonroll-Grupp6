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

private:
	void Explode();
	virtual void Attack() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionRadius;

	
};
