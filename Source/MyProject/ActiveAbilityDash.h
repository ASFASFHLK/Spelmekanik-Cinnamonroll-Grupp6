// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RivetGameplayAbility.h"
#include "ActiveAbilityDash.generated.h"

class ABaseCharacter;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UActiveAbilityDash : public URivetGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	
private:
	bool CanDash = true;
	UPROPERTY(EditAnywhere, Category = "Ability")
	float DashDistance;

	UPROPERTY(EditAnywhere, Category = "Ability")
	bool IsDashing;

	UPROPERTY(EditAnywhere, Category = "Ability")
	float DashCoolDown;

	UPROPERTY()
	float Timer;

	void Dash(ABaseCharacter* Character);
	
};
