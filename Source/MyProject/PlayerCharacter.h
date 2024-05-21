// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"


class UModifierComponent;
class UNiagaraSystem;
class UCameraComponent;
class USpringArmComponent;
class AGunBase;
class URivetGameplayAbility;
class URivetAbilitySystemComponent;
class URivetAttributeSet;

/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()



private:
	UPROPERTY(EditAnywhere,Category="Equipment")
	TSubclassOf<AGunBase> EquipedGun; // Please use me😭
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CharacterCamera;

	UPROPERTY()
	AGunBase* Gun = nullptr;
	
	UPROPERTY(EditAnywhere)
	float AirTime = 3;

	/**********************
	 Camera settings
	****************/
	UPROPERTY(EditAnywhere, Category="Camera Controll")
	float LookUpSpeed = 2.0;

	UPROPERTY(EditAnywhere, Category="Camera Controll")
	float LookSideSpeed = 2.0;

	UPROPERTY(EditAnywhere, Category="Camera Controll")
	bool InvertCamera = false;

	/**********************
	 Control related stuff
	 ****************/
	UFUNCTION()
	void LookUp(float Value);
	
	UFUNCTION()
	void LookSides(float Value);
	
	UFUNCTION(BlueprintCallable)
	void Shoot() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess= true), Category = "Sound")
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess= true), Category = "Sound")
	USoundBase* HitSound;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	bool StartWithHudVisible = true;

	UPROPERTY()
	bool IsInvulnerable;
	
public:
	UPROPERTY()
	float DefaultMovementSpeed = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="Player Mesh")
	USkeletalMeshComponent* PlayerFirstPersonMesh;
	
	void SetGun(AGunBase* NewGun);
	
	UFUNCTION(BlueprintCallable)
	void UpdateVariables();

	UFUNCTION(BlueprintCallable)
	float GetLookSpeed() const {return LookSideSpeed;}

	UFUNCTION(BlueprintCallable)
	void SetLookUpSpeed(const float Value){LookUpSpeed = Value;}
	
	UFUNCTION(BlueprintCallable)
	void SetLookSidesSpeed(const float Value){LookSideSpeed = Value;}

	UFUNCTION(BlueprintCallable)
	void SetIsInvulnerable(bool Value){IsInvulnerable = Value;}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DashVisuals();

	UFUNCTION(BlueprintCallable)
	void SetMouseInverted(const bool Inverted);
	
public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaSeconds) override;
};
