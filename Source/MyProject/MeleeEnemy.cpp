// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"

#include "KismetTraceUtils.h"
#include "Engine/DamageEvents.h"

void AMeleeEnemy::Attack()
{
	Super::Attack();
	FVector test = (GetActorForwardVector() * 100) + GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	
	
	UKismetSystemLibrary::SphereTraceSingle(this,GetActorLocation(),test,20,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),false,
		ActorsToIgnore, EDrawDebugTrace::None,HitResult,true,
		FColor::Red, FColor::Green, 0.f);

	if(AActor* ActorHit = HitResult.GetActor())
	{
		ActorHit->TakeDamage(DamageDealt, FDamageEvent(), GetController(), this);
		
	}
	
	
}
