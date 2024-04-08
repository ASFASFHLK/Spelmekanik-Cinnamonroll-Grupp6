// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class AGunBase;
/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere,Category="Equipment")
	TSubclassOf<AGunBase> EquipedGun;
};
