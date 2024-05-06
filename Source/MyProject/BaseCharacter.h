// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UHealthComp;
class URivetAttributeSet;
class URivetGameplayAbility;
class URivetAbilitySystemComponent;

UCLASS()
class MYPROJECT_API ABaseCharacter : public ACharacter,  public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	UHealthComp* GetHealthComponent() const {return HealthComp;}
	
	UFUNCTION()
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintNativeEvent)
    void OnTakeDamage();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UHealthComp* HealthComp;
	
	UPROPERTY(EditDefaultsOnly)
	float JumpHeight;
	
	UFUNCTION()
	virtual void MoveForward(float Value);
	UFUNCTION()
	virtual void MoveSides(float Value);
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 300.0f;
	UPROPERTY()
	bool bIsParried = false;
	UPROPERTY()
	FTimerHandle ParryTimerHandle = FTimerHandle();
	virtual float InternalTakeRadialDamage(float Damage, FRadialDamageEvent const& RadialDamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	
	virtual void HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	friend URivetAttributeSet;

	/**********************
	Ability System Components 
	****************/
	TObjectPtr<URivetAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<URivetAttributeSet> Attributes;

	/***********
		*Overrides 
	************/
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**********************
	 Ability System stuff
	 ****************/
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const;
	void AddStartupGameplayAbilities();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilites")
	TArray<TSubclassOf<class UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilites")
	TArray<TSubclassOf<URivetGameplayAbility>> GameplayAbilities;
	
	friend URivetAttributeSet;
	
	UPROPERTY()
	uint8 bAbilitiesInitialized:1;



	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input


	void ApplyStun(float TimeStunned);
	void ResetStun() const;
	UFUNCTION()
	void Parry();
	UFUNCTION()
	void StopBeingParried();

private:
	float StunTimer;
	bool IsStunned;
	void ResetStun();

};
