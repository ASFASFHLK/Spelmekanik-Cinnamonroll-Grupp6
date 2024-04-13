// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBarrel.h"
#include "WaterBarrel.generated.h"

class ABaseEnemy;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AWaterBarrel : public ABaseBarrel
{
	GENERATED_BODY()

	virtual void Explode(AController* EventInstigator) override;
private:
	UPROPERTY(EditAnywhere, Category = "Ability")
	float TimeStunned;
	
};
