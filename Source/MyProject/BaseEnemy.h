// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemy.generated.h"

class ASquad;
class AAIController;
DECLARE_DYNAMIC_DELEGATE(FOnDeath);

UCLASS()
class MYPROJECT_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentTarget() const {return CurrentTarget;}

	UFUNCTION(BlueprintCallable)
	ABaseEnemy* GetPartner() const {return Partner;}

	float GetCurrentAttackCooldown() const{return CurrentAttackCooldown;}

	float GetTargetIsCloseRange() const{return TargetIsCloseRange;}

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool HasPartner() const;

	void SetSquad(ASquad* NewSquad) {MySquad = NewSquad;}

	void AlertPartnerOfDeath();
	
	void MyPartnerHasDied();

	
	
	void SetPartner(ABaseEnemy* NewPartner) {Partner = NewPartner;}
	
	FOnDeath OnDeath;
	
	virtual void Attack();


protected:
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float DamageDealt = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "Squad")
	ASquad* MySquad;
	
	virtual void Tick(float DeltaSeconds) override;

private:
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	AActor* CurrentTarget;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AggroRange;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackCooldown;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float TargetIsCloseRange;

	UPROPERTY()
	float CurrentAttackCooldown;
	
	
	
	UPROPERTY(VisibleAnywhere, Category = "Squad")
	ABaseEnemy* Partner;
};

