// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UModifierComponent;
class UNiagaraSystem;
class UCameraComponent;
class USpringArmComponent;
class AGunBase;
/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UModifierComponent* ModifierComponent;

private:
	UPROPERTY(EditAnywhere,Category="Equipment")
	TSubclassOf<AGunBase> EquipedGun;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CharacterCamera;

	UPROPERTY()
	bool bCanShoot = true;
	UPROPERTY()
	float ReloadTime = 3;
	UPROPERTY()
	float BurstTime = 0.1f;
	UPROPERTY()
	int Pellets = 12;
	UPROPERTY()
	float Damage = 2;
	UPROPERTY()
	int Bursts = 5;
	UPROPERTY()
	FTimerHandle ShootTimerHandle = FTimerHandle();
	
	UPROPERTY(EditAnywhere, Category="Camera Controll")
	float LookUpSpeed = 2.0;

	UPROPERTY(EditAnywhere, Category="Camera Controll")
	float LookSideSpeed = 2.0;

	UPROPERTY(EditAnywhere, Category="Camera Controll")
	bool InvertCamera = false;

	UFUNCTION()
	void Reload();
	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION()
	void UseShotGun();
	UFUNCTION()
	void ShotGunShot();
	
	UFUNCTION()
	void LookUp(float Value);
	
	UFUNCTION()
	void LookSides(float Value);
	
	UFUNCTION(BlueprintCallable)
	void Shoot();


	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess= true), Category = "Gun")
	UNiagaraSystem* ShotEffect;
	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess= true), Category = "Gun")
	USoundBase* ShotSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess= true), Category = "Sound")
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess= true), Category = "Sound")
	USoundBase* HitSound;


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess= true), Category = "Gameplay")
	FVector MuzzleOffset = FVector(100,0,10);

	UPROPERTY(EditDefaultsOnly, Category="Player Mesh")
	USkeletalMeshComponent* PlayerFirstPersonMesh;

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};
