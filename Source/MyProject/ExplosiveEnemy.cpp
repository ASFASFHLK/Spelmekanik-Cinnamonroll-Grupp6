// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveEnemy.h"

#include "HealthComp.h"
#include "Squad.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
/*
void AExplosiveEnemy::SetIsBeingThrown(bool Value)
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(MyBlackBoard)
	{
		MyBlackBoard->SetValueAsBool("BeingThrown", Value);
	}
}
*/

void AExplosiveEnemy::Attack()
{
	Super::Attack();
	if(!DoingAttack)
	{
		Explode();
		DoingAttack = true;
	}
}


void AExplosiveEnemy::ResetEnemy()
{
	SetIsBeingThrown(false);
	DoingAttack = false;
	Super::ResetEnemy();
}

bool AExplosiveEnemy::CanBeThrown()
{
	if(MySquad)
	{
		if(const float DistanceToPlayer = FVector::Distance(GetActorLocation(), MySquad->GetPlayerLocation()); DistanceToPlayer > 750)
		{
			return true;
		}
	}
	return false;
}

/*
void AExplosiveEnemy::Explode()
{
	const TArray<AActor*> ActorsToIgnore;
	
	UGameplayStatics::ApplyRadialDamage(this, DamageDealt, GetActorLocation(),
		ExplosionRadius,DamageType,ActorsToIgnore, this, GetController(),
		true, ECC_Pawn);

	DrawDebugSphere(GetWorld(),GetActorLocation(),ExplosionRadius,12,FColor::Red,false,3.f);
	//const bool Discard = OnDeath.ExecuteIfBound();
	HasDied();
}
*/

