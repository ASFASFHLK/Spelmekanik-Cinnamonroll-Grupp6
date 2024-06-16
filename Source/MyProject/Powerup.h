// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "Powerup.generated.h"

class UCapsuleComponent;

UCLASS()
class MYPROJECT_API APowerup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerup();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> PickUpEffect;  

	UPROPERTY(EditDefaultsOnly)
	bool ShouldRespawn = false;
	UPROPERTY(EditDefaultsOnly)
	float RespawnTime = 5; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* PickUpMesh;
	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;
	
	FActiveGameplayEffectHandle EffectHandle; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
