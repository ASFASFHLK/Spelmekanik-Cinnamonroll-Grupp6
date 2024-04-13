// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBarrel.generated.h"

UCLASS()
class MYPROJECT_API ABaseBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	class UHealthComp* HealthComp;

	virtual void Explode(AController* EventInstigator);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Explosion")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float DamageDealt;

	UPROPERTY()
	bool Exploded;

	
};
