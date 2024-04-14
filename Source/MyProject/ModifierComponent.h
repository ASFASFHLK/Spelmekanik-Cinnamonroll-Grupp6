// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ModifierComponent.generated.h"


class ABaseModifier;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UModifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UModifierComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeModifiers(TSubclassOf<ABaseModifier> NewModifier, const int ModifierPlace);
	
public:
	UPROPERTY(BlueprintReadWrite)
	ABaseModifier* ModifierOne;
	
	UPROPERTY(VisibleAnywhere)
	ABaseModifier* ModifierTwo;
		
};
