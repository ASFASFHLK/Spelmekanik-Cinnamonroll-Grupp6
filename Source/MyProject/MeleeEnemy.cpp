// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"

#include "HealthComp.h"
#include "KismetTraceUtils.h"
#include "Engine/DamageEvents.h"


void AMeleeEnemy::Attack()
{
	Super::Attack();
	FVector test = (GetActorForwardVector() * 100) + GetActorLocation();
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	
	
	UKismetSystemLibrary::SphereTraceSingle(this,GetActorLocation(),test,20,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),false,ActorsToIgnore, EDrawDebugTrace::ForDuration,HitResult,true,
		FColor::Red, FColor::Green, 1.5f);

	ABaseCharacter* ActorHit = Cast<ABaseCharacter>(HitResult.GetActor());
	if(ActorHit)
	{


		ActorHit->TakeDamage(DamageDealt, FDamageEvent(), GetController(), this);

		//Implement for the ActorHit to take damage
		

	}
	
	
}
