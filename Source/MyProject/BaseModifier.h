// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseModifier.generated.h"

class APlayerCharacter;

UCLASS()
class MYPROJECT_API ABaseModifier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseModifier();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	int AmountsEquipped = 1;
	UPROPERTY(BlueprintReadOnly)
	bool CanHaveDuplicates = true;
	bool WantsUpdate = true;
	FString Identifier = ""; 

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetIdentifier(const FString& Identity); 
	FString GetIdentifier() const;
	
	virtual void OnAdded();
	UFUNCTION()
	virtual void OnUpdate(float DeltaTime);
	
	virtual void OnRemoved();
	
	UFUNCTION(BlueprintPure)
	int GetAmountsEquipped() const;

	UFUNCTION(BlueprintCallable)
	virtual void AddDuplicate();

	UFUNCTION(BlueprintCallable)
	bool GetCanHaveDuplicates() const;

	UFUNCTION(BlueprintPure)
	bool GetWantsUpdate() const;
	
};
