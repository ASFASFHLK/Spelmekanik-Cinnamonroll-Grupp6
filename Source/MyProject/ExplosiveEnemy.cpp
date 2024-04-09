// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveEnemy.h"

void AExplosiveEnemy::Attack()
{
	Super::Attack();

	UE_LOG(LogTemp, Display, TEXT("Explosion"));
	Destroy();
}
