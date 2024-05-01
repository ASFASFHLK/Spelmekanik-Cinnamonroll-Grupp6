// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseModifier.h"
#include "DoubleJumpModifier.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ADoubleJumpModifier : public ABaseModifier
{
	GENERATED_BODY()

public:
	virtual void AddDuplicate() override;
	
private:
	virtual void OnAdded() override;
	virtual void OnRemoved() override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	int32 ExtraJumps;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	int32 DuplicateExtraJumps;
	UPROPERTY()
	int32 OriginalNumberOfJumps;

};
