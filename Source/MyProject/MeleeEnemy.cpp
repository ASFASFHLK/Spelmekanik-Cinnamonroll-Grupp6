// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"

#include "KismetTraceUtils.h"

void AMeleeEnemy::Attack()
{
	Super::Attack();
	FVector test = (GetActorForwardVector() * 100) + GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	TArray<EObjectTypeQuery> ObjectTypes;
	
	
	UKismetSystemLibrary::SphereTraceSingle(this,GetActorLocation(),test,20,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),false,ActorsToIgnore, EDrawDebugTrace::ForDuration,HitResult,true,
		FColor::Red, FColor::Green, 30.f);

	ABaseCharacter* ActorHit = Cast<ABaseCharacter>(HitResult.GetActor());
	if(ActorHit)
	{
		//Implement for the ActorHit to take damage
		
	}
	
	
}
