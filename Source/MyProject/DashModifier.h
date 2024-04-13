// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseModifier.h"
#include "DashModifier.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ADashModifier : public ABaseModifier
{
	GENERATED_BODY()

	virtual void OnAdded() override;
	virtual void OnRemoved() override;

private:
	UPROPERTY(EditAnywhere, Category = "Ability")
	float DashDistance;

	UPROPERTY(EditAnywhere, Category = "Ability")
	bool IsDashing;

	void Dash();
};
