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
	UFUNCTION(BlueprintPure)
	FString GetHealthAsText() const;
	UFUNCTION(BlueprintCallable)
	void SetHealthToMax(); 
	
	UFUNCTION(BlueprintCallable)
	void SetHealthModifier (int NewHealthModifier);

	UFUNCTION(BlueprintCallable)
	void ResetHealth();

	UFUNCTION(BlueprintPure)
	int32 GetMaxHealth() const;
	
	UFUNCTION(BlueprintPure)
	int GetCurrentHealth() const;

	UFUNCTION()
	void SetCurrentHealth(const int NewHealth){CurrentHealth = NewHealth;}
	
	UFUNCTION(BlueprintCallable)
	bool TakeDamage(const  int DamageToTake);
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(const int32 NewMaxHealthValue );
	
	UPROPERTY(EditDefaultsOnly)
	bool AllowHealthCompToSetHealth = true;
	UFUNCTION(BlueprintCallable)
	void AddHealth(const int HealthToAdd);
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int MaxHealth = 100;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int CurrentHealth = 0;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	int HealthModifier = 0; 

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
