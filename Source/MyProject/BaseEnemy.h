// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "Poolable.h"
#include "BaseEnemy.generated.h"

class AEnemyAIController;
class ASquad;
class AAIController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class MYPROJECT_API ABaseEnemy : public ABaseCharacter, public IPoolable
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ScaleHealthAndDamage(float Health, float Damage);

	UFUNCTION()
	FVector GetPlayerLocationFromSquad() const;
	
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentTarget() const {return CurrentTarget;}

	UFUNCTION(BlueprintCallable)
	ABaseEnemy* GetPartner() const {return Partner;}

	UFUNCTION(BlueprintCallable)
	virtual void HasDied();

	UFUNCTION(BlueprintNativeEvent)
	void Ragdoll();

	UFUNCTION(BlueprintCallable)
	virtual void ResetEnemy();

	UFUNCTION()
	float GetCurrentAttackCooldown() const{return CurrentAttackCooldown;}

	UFUNCTION()
	float GetTargetIsCloseRange() const{return TargetIsCloseRange;}

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//bool HasPartner() const;

	UFUNCTION(BlueprintCallable)
	void SetSquad(ASquad* NewSquad) {MySquad = NewSquad;}

	UFUNCTION(BlueprintCallable)
	ASquad* GetMySquad() const {return MySquad;}
	
	//void MyPartnerHasDied();
	
	UFUNCTION()
	void SetPartner(ABaseEnemy* NewPartner) {Partner = NewPartner;}

	UFUNCTION(BlueprintCallable)
	float GetDamage() const {return DamageDealt;}

	UFUNCTION(BlueprintCallable)
	bool GetIsAlive() const {return IsAlive;}

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	
	virtual void Attack();

	UFUNCTION(BlueprintImplementableEvent)
	void TakeDamageVisual();


protected:
	UPROPERTY(EditAnywhere, Category="Combat")
	float DamageDealt = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "Squad")
	ASquad* MySquad;

	UPROPERTY()
	AEnemyAIController* MyController;

	UPROPERTY(BlueprintReadWrite)
	UBlackboardComponent* MyBlackBoard;

	UPROPERTY()
	bool IsAlive = true;

	UPROPERTY(EditAnywhere, Category = "Combat")
	AActor* CurrentTarget;
	
	virtual void Tick(float DeltaSeconds) override;

	

private:

	UPROPERTY()
	int OriginalDamage;

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

