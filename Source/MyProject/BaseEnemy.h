// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemy.generated.h"


UCLASS()
class MYPROJECT_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentTarget() const {return CurrentTarget;}

private:
	UPROPERTY(EditAnywhere)
	AActor* CurrentTarget;

	UPROPERTY(EditAnywhere)
	float AggroRange;

	UPROPERTY(EditAnywhere)
	float AttackCooldown;
};

