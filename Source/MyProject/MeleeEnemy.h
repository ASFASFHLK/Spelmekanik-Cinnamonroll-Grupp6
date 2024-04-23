// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "MeleeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMeleeEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void ThrowExplosiveEnemy();

private:
	virtual void Attack() override;

	

};
