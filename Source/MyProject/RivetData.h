// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#define E_RIVET_ABILITY_INPUT_ID_TEXT "None", "Confirm", "Cancel", "Dash", "TimeSlow", "Parry"
	
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


