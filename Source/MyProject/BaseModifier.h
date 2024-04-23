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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText ModifierName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText ModifierDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText ModifierFlavourText; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnAdded();
	UFUNCTION()
	virtual void OnUpdate(float DeltaTime);
	virtual void OnRemoved();

};
