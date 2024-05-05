// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
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
class MYPROJECT_API APlayerCharacter : public ABaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	// Legacy 
	UModifierComponent* ModifierComponent;

	/***********
	 *Overrides 
	 ************/
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**********************
	 Ability System stuff
	 ****************/
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void AddStartupGameplayAbilities();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilites")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilites")
	TArray<TSubclassOf<URivetGameplayAbility>> GameplayAbilities;


	
	UPROPERTY()
	uint8 bAbilitiesInitialized:1;

	
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
	
	UFUNCTION(BlueprintCallable)
	void CancelShot() const;

	/**********************
	Ability System Components 
	****************/
	TObjectPtr<URivetAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<URivetAttributeSet> Attributes;

	
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	bool StartWithHudVisible = true;
	
public:
	UPROPERTY()
	float DefaultMovementSpeed = 0;
	UPROPERTY(EditDefaultsOnly, Category="Player Mesh")
	USkeletalMeshComponent* PlayerFirstPersonMesh;
	UFUNCTION(BlueprintCallable)

	void ShowHud(const bool Show);

	void SetGun(AGunBase* NewGun);

	
public:
	APlayerCharacter();
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaSeconds) override;
};
