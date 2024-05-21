// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Poolable.h"
#include "GameFramework/Actor.h"
#include "RangedEnemyProjectile.generated.h"

class ABaseCharacter;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MYPROJECT_API ARangedEnemyProjectile : public AActor, public IPoolable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	ARangedEnemyProjectile();
	
	UFUNCTION()
	void ParriedPorjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void DealDamage(ABaseCharacter* Character);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	UFUNCTION(BlueprintCallable)
	void SetDamage(const int NewDamage){DamageDealt = NewDamage;}

	virtual void SetOwner(AActor* NewOwner) override;
	
	
private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	int DamageDealt;
	
	UPROPERTY()
	AActor* ProjectileOwner;
	

	
};
