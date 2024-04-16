// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "Enemy_Spawner.h"
#include "HealthComp.h"
#include "Squad.h"
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

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                             AActor* DamageCauser)
{
	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if(DamageTaken >= HealthComp->GetCurrentHealth()) // If we die 
	{
		AlertPartnerOfDeath();
		// calls the event
		if(!OnDeath.ExecuteIfBound())
		{
			//UE_LOG(LogTemp, Warning, TEXT("I should have a deligate bound to me %c"), GetName());
		}	
		OnDeath.Clear();
		Destroy();
	}
	
	return DamageTaken;
}

bool ABaseEnemy::HasPartner() const
{
	if(Partner == nullptr)
	{
		return false;
	}
	return true;
}

void ABaseEnemy::AlertPartnerOfDeath()
{
	if (Partner != nullptr)
	{
		Partner->MyPartnerHasDied();
	}

	MySquad->RemoveFromSquad(this);
}

void ABaseEnemy::MyPartnerHasDied()
{
	Partner = nullptr;
	MySquad->FindNewPartner(this);
}


void ABaseEnemy::Attack()
{
	CurrentAttackCooldown = AttackCooldown;
}


