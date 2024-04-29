// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
class UHealthComp;
UCLASS()
class MYPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	UHealthComp* GetHealthComponent() const {return HealthComp;}
	
	UFUNCTION()
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UHealthComp* HealthComp;
	
	UPROPERTY(EditDefaultsOnly)
	float JumpHeight;
	
	UFUNCTION()
	virtual void MoveForward(float Value);
	UFUNCTION()
	virtual void MoveSides(float Value);

	UFUNCTION()
	virtual void MoveForwardAxis(float Value);
	UFUNCTION()
	virtual void MoveSidesAxis(float Value);
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 300.0f;
	UPROPERTY()
	bool bIsParried = false;
	UPROPERTY()
	FTimerHandle ParryTimerHandle = FTimerHandle();
	virtual float InternalTakeRadialDamage(float Damage, FRadialDamageEvent const& RadialDamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ApplyStun(float TimeStunned);
	void ResetStun() const;
	UFUNCTION()
	void Parry();
	UFUNCTION()
	void StopBeingParried();

private:
	float StunTimer;
	bool IsStunned;
	void ResetStun();

};
