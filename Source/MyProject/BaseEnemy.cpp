// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "EnemyAIController.h"
#include "Enemy_Spawner.h"
#include "ExplosiveEnemy.h"
#include "HealthComp.h"
#include "Squad.h"
#include "Kismet/GameplayStatics.h"


void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();
	CurrentTarget = UGameplayStatics::GetPlayerCharacter(this, 0);
	CurrentAttackCooldown = 0;
	MyController = Cast<AEnemyAIController>(GetController());
	OriginalDamage = DamageDealt;
	OriginalHealth = HealthComp->GetMaxHealth();
	
	if(MyController)
	{
		MyBlackBoard = MyController->GetBlackboardComponent();
	}
}

void ABaseEnemy::ScaleHealthAndDamage(const float Health, const float Damage)
{
	DamageDealt = OriginalDamage * Damage;
	float Temp = OriginalHealth*Health;
	HealthComp->SetMaxHealth(Temp);
	HealthComp->SetHealthToMax();
	
	
	
}

FVector ABaseEnemy::GetPlayerLocationFromSquad() const
{
	if(MySquad)
	{
		return MySquad->GetPlayerLocation();
	}

	return {};
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
	if(DamageCauser->IsA(ABaseEnemy::StaticClass()))
	{
		Super::TakeDamage(0, DamageEvent, EventInstigator, DamageCauser);
		return 0;
	}

	const float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(IsAlive)
	{
		TakeDamageVisual();
	}
	
	
	if(0 >= HealthComp->GetCurrentHealth()) // If we die 
	{
		if(IsAlive)
		{
			HasDied();
		}
	}
	
	return DamageTaken;
}

/*
bool ABaseEnemy::HasPartner() const
{
	if(Partner == nullptr)
	{
		return false;
	}
	return true;
}



void ABaseEnemy::MyPartnerHasDied()
{
	Partner = nullptr;
	if(MySquad)
	{
		MySquad->FindNewPartner(this);
	}
}
*/

void ABaseEnemy::HasDied()
{
	
	if(MySquad)
	{
		MySquad->RemoveFromSquad(this);
	}
	
	// calls the event
	if(OnDeath.IsBound())
	{
		OnDeath.Broadcast();
	}	
	OnDeath.Clear();
	IsAlive = false;
	Ragdoll();
}

void ABaseEnemy::ResetEnemy()
{
	IsAlive = true;
	Partner = nullptr;
	HealthComp->ResetHealth();
}

void ABaseEnemy::Ragdoll_Implementation()
{
}


void ABaseEnemy::Attack()
{
	CurrentAttackCooldown = AttackCooldown;
}


