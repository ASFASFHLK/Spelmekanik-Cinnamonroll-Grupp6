// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangedEnemyProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class MYPROJECT_API ARangedEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangedEnemyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor,
		UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UPROPERTY(BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	virtual void SetOwner(AActor* NewOwner) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float DamageDealt;

	UPROPERTY()
	AActor* ProjectileOwner;
	

	
};
