// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#define ERivetAbilityInputIDText "None", "Confirm", "Cancel", "Dash", "TimeSlow", "Parry"
	
UENUM(BlueprintType)
enum class ERivetAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Dash,
	TimeSlow,
	Parry
};


class MYPROJECT_API RivetData
{
public:
	RivetData();
	~RivetData();
};
