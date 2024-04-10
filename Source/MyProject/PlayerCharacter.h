// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
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


	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CharacterCamera;

	UPROPERTY(EditAnywhere, Category="Camera Controll")
	float LookUpSpeed = 2.0;

	UPROPERTY(EditAnywhere, Category="Camera Controll")
	float LookSideSpeed = 2.0;

	UPROPERTY(EditAnywhere, Category="Camera Controll")
	bool InvertCamera = false;
	
	UFUNCTION()
	void LookUp(float Value);
	
	UFUNCTION()
	void LookSides(float Value);

	UPROPERTY(EditDefaultsOnly, Category="Player Mesh")
	USkeletalMeshComponent* PlayerFirstPersonMesh;

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
