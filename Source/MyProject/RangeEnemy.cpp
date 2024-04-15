// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeEnemy.h"

#include "RangedEnemyProjectile.h"

ARangeEnemy::ARangeEnemy()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void ARangeEnemy::Attack()
{
	Super::Attack();
	
	FVector Location = GetActorLocation() + FVector(100,0, 0);
	FRotator Rotation = GetActorRotation();
	
	FActorSpawnParameters SpawnInfo;
	ARangedEnemyProjectile* SpawnedProjectile =  GetWorld()->SpawnActor<ARangedEnemyProjectile>(Projectile, Location,
		Rotation, SpawnInfo);

	if(SpawnedProjectile)
	{
		SpawnedProjectile->SetOwner(this);
	}
}
