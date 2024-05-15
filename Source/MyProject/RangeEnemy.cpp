 // Fill out your copyright notice in the Description page of Project Settings.


#include "RangeEnemy.h"

#include "RangedEnemyProjectile.h"

ARangeEnemy::ARangeEnemy()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

 void ARangeEnemy::Flee_Implementation()
 {
 }

 void ARangeEnemy::LockInPlace_Implementation()
 {
 }

 void ARangeEnemy::Attack()
{
	Super::Attack();
	if(bIsParried)
	{
		return;
	}



	const FActorSpawnParameters SpawnInfo;

	if(ARangedEnemyProjectile* SpawnedProjectile =  GetWorld()->SpawnActor<ARangedEnemyProjectile>(Projectile, ProjectileSpawnPoint->GetComponentLocation(),
		GetActorRotation(), SpawnInfo))
	{
		SpawnedProjectile->SetOwner(this);
		SpawnedProjectile->SetDamage(DamageDealt);
	}
}
