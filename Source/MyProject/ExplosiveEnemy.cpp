// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveEnemy.h"

#include "HealthComp.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"

void AExplosiveEnemy::Attack()
{
	Super::Attack();
	Explode();
}

void AExplosiveEnemy::Explode()
{
	const FVector Height = GetActorUpVector() + GetActorLocation();
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;

	UKismetSystemLibrary::SphereTraceSingle(this,Height,Height,ExplosionRadius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,ActorsToIgnore, EDrawDebugTrace::ForDuration,HitResult,true,
		FColor::Red, FColor::Green, 2.f);

	if(AActor* ActorHit = HitResult.GetActor())
	{
		ActorHit->TakeDamage(DamageDealt, FDamageEvent(),
			GetController(), this);
		
	}
	Destroy();
}
