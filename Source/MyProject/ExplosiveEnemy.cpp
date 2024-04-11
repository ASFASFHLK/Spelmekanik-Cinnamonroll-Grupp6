// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveEnemy.h"

#include "HealthComp.h"
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
	
	
	UKismetSystemLibrary::SphereTraceSingle(this,GetActorLocation(),Height,ExplosionRadius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,ActorsToIgnore, EDrawDebugTrace::ForDuration,HitResult,true,
		FColor::Red, FColor::Green, 30.f);

	ABaseCharacter* ActorHit = Cast<ABaseCharacter>(HitResult.GetActor());
	if(ActorHit)
	{
		ActorHit->GetHealthComponent()->TakeDamage(Damage);
	}
}
