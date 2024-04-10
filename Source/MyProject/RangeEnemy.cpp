// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeEnemy.h"

#include "RangedEnemyProjectile.h"

void ARangeEnemy::Attack()
{
	Super::Attack();
	FVector Location = GetActorLocation();
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ARangedEnemyProjectile>(Projectile, Location, Rotation, SpawnInfo);
}
