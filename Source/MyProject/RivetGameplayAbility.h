// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RivetData.h"
#include "Abilities/GameplayAbility.h"
#include "RivetGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API URivetGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	URivetGameplayAbility();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Abilities")
	ERivetAbilityInputID AbilityInputID{ERivetAbilityInputID::None};
	
};
