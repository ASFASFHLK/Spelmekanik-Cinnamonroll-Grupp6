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

private:
	virtual void Attack() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ARangedEnemyProjectile> Projectile;
};

