// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "Enemy_Spawner.h"
#include "HealthComp.h"
#include "Kismet/GameplayStatics.h"


void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentTarget = UGameplayStatics::GetPlayerCharacter(this, 0);
	CurrentAttackCooldown = 0;
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CurrentAttackCooldown >= 0)
	{
		CurrentAttackCooldown -= DeltaSeconds;
	}
}

<<<<<<< Updated upstream
=======

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if(DamageTaken >= HealthComp->GetCurrentHealth()) // If we die 
	{
		UE_LOG(LogTemp, Display, TEXT("I am dead"));
		if(OnDeath.IsBound())
		{
			UE_LOG(LogTemp, Display, TEXT("I am bound"));
		}
		OnDeath.ExecuteIfBound(); // calls the event 
	}
	
	return DamageTaken;
}

>>>>>>> Stashed changes
void ABaseEnemy::Attack()
{
	CurrentAttackCooldown = AttackCooldown;
}


