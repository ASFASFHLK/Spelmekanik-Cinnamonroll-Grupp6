// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"

#include "AIController.h"
#include "HealthComp.h"
#include "KismetTraceUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"



void AMeleeEnemy::ThrowExplosiveEnemy_Implementation()
{
	
}

void AMeleeEnemy::CallPartnerToMove_Implementation()
{
}



void AMeleeEnemy::SetCanThrow_Implementation(bool Value)
{
}

void AMeleeEnemy::ResetThrowTimer()
{
	CurrentThrowTimer = ThrowTimer;
	SetCanThrow(false);
}

void AMeleeEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentThrowTimer -= DeltaSeconds;
	if(CurrentThrowTimer <= 0)
	{
		SetCanThrow(true);
	}
}

void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentThrowTimer = 0;
}


void AMeleeEnemy::Attack()
{
	Super::Attack();
	if(bIsParried)
	{
		return;
	}
	const FVector End = (GetActorForwardVector() * 100) + GetActorLocation();
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	
	
	UKismetSystemLibrary::SphereTraceSingle(this,GetActorLocation(),End,50,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),false,ActorsToIgnore, EDrawDebugTrace::ForDuration,HitResult,true,
		FColor::Red, FColor::Green, 1.5f);

	if(ABaseCharacter* ActorHit = Cast<ABaseCharacter>(HitResult.GetActor()))
	{
		ActorHit->TakeDamage(DamageDealt, FDamageEvent(), GetController(), this);

	}
}
