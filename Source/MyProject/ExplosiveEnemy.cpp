// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveEnemy.h"

#include "HealthComp.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
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
	

	UGameplayStatics::ApplyRadialDamage(this, DamageDealt, GetActorLocation(),
		ExplosionRadius,DamageType,ActorsToIgnore, this, GetController(),
		true, ECC_Pawn);

	DrawDebugSphere(GetWorld(),GetActorLocation(),ExplosionRadius,12,FColor::Red,false,3.f);
	Destroy();
}
