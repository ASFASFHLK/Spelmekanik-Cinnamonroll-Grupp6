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

	float GetCurrentAttackCooldown() const{return CurrentAttackCooldown;}

	float GetTargetIsCloseRange() const{return TargetIsCloseRange;}

	
	virtual void Attack();

private:

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	AActor* CurrentTarget;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AggroRange;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackCooldown;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float TargetIsCloseRange;

	UPROPERTY()
	float CurrentAttackCooldown;
};

