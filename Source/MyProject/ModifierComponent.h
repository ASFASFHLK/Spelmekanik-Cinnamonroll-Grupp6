// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ModifierComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdate, float, update);

class ABaseModifier;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UModifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UModifierComponent();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int MaxModifiersAllowed = 3;
	
	FOnUpdate ModifierUpdates;

	void AddNewModifier(const TSubclassOf<ABaseModifier> NewModifier,const FString& Identifier,  const int ModifierPlace, TArray<ABaseModifier*>& List);
	void RemoveModifer(const int ModifierPlace, TArray<ABaseModifier*>& List);

	// Modifier containers 
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess= "true"))
	TArray<ABaseModifier*> Modifiers;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess= "true"))
	TArray<ABaseModifier*> DefaultModifiers_Internal;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ABaseModifier>> DefaultModifiers; 
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeModifiers(TSubclassOf<ABaseModifier> NewModifier, const int ModifierPlace);
	
	UFUNCTION(BlueprintCallable)
	void SetMaxModifiersAllowed(const int NewValue);
	
	UFUNCTION()
	void SetUp();
	
	UFUNCTION(BlueprintPure)
	bool HasItemInSlot(const int SlotIndex) const;

	UFUNCTION(BlueprintPure)
	bool HasModifierEquipped() const;
	
	
};
