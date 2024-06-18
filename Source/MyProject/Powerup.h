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

	UPROPERTY(EditDefaultsOnly)
	float MaxFloatHeight = 10;

	UPROPERTY(EditAnywhere)
	float Duration = 5;

	UFUNCTION(BlueprintNativeEvent)
	void ItemPickedUped();

	UFUNCTION(BlueprintNativeEvent)
	void ItemRespawned();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* PickUpMesh;
	
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* CapsuleComponent;
	
	FActiveGameplayEffectHandle EffectHandle;
	bool IsRespawning = false; 
	float Accumulator = 0;

	void SetComponentsActive( const bool State); 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText NameOfAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText Description;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
