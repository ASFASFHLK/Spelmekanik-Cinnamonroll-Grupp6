// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"

class URivetAttributeSet;

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
	bool TakeDamage(const  int DamageToTake);
	
	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(const int32 NewMaxHealthValue );
	
	UPROPERTY(EditDefaultsOnly)
	bool AllowHealthCompToSetHealth = true;
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	URivetAttributeSet* AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int32 MaxHealth = 100;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int CurrentHealth = 0;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int HealthModifier = 0; 

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
