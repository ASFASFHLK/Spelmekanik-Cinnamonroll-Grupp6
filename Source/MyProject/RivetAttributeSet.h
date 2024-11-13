// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "RivetAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class MYPROJECT_API URivetAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	URivetAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category= "Attributes")
	FGameplayAttributeData Health = 0;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, Health)
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category= "Attributes")
	FGameplayAttributeData MaxHealth = 0;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, MaxHealth)
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armour, Category= "Attributes")
	FGameplayAttributeData Armour = 0;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, Armour)
	UFUNCTION()
	virtual void OnRep_Armour(const FGameplayAttributeData& OldValue);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TestHealth, Category= "Attributes")
	FGameplayAttributeData TestHealth = 0;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, TestHealth)
	UFUNCTION()
	virtual void OnRep_TestHealth(const FGameplayAttributeData& OldValue);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TestMaxHealth, Category= "Attributes")
	FGameplayAttributeData TestMaxHealth = 0;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, TestMaxHealth)
	UFUNCTION()
	virtual void OnRep_TestMaxHealth(const FGameplayAttributeData& OldValue);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Damage, Category= "Attributes")
	FGameplayAttributeData Damage = 10;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, Damage)
	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Speed, Category= "Attributes")
	FGameplayAttributeData Speed = 700;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, Speed)
	UFUNCTION()
	virtual void OnRep_Speed(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_JumpCount, Category= "Attributes")
	FGameplayAttributeData JumpCount = 1;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, JumpCount)
	UFUNCTION()
	virtual void OnRep_JumpCount(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_JumpHeight, Category= "Attributes")
	FGameplayAttributeData JumpHeight = 1;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, JumpHeight)
	UFUNCTION()
	virtual void OnRep_JumpHeight(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExplosionRadius, Category= "Attributes")
	FGameplayAttributeData ExplosionRadius = 1;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, ExplosionRadius)
	UFUNCTION()
	virtual void OnRep_ExplosionRadius(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExplosionChargeRate, Category= "Attributes")
	FGameplayAttributeData ExplosionChargeRate = 1;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, ExplosionChargeRate)
	UFUNCTION()
	virtual void OnRep_ExplosionChargeRate(const FGameplayAttributeData& OldValue);
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExtraCredits, Category= "Attributes")
	FGameplayAttributeData ExtraCredits = 0;
	ATTRIBUTE_ACCESSORS(URivetAttributeSet, ExtraCredits)
	UFUNCTION()
	virtual void OnRep_ExtraCredits(const FGameplayAttributeData& OldValue);
	
	void AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
		const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;

	UPROPERTY()
	APlayerCharacter* Player; 
};
