// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComp();
	
	UFUNCTION(BlueprintCallable)
	void SetHealthModifier (int NewHealthModifier);

	UFUNCTION(BlueprintPure)
	int32 GetMaxHealth() const;
	
	UFUNCTION(BlueprintPure)
	int GetCurrentHealth() const;
	
	UFUNCTION(BlueprintCallable)
	bool TakeDamage(int DamageToTake);
	
	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHealth = 100;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int CurrentHealth = 0;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int HealthModifier = 0; 

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
