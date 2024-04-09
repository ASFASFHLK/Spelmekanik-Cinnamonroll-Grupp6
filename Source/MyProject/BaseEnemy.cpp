// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"


void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentTarget = UGameplayStatics::GetPlayerCharacter(this, 0);
	CurrentAttackCooldown = 0;
}

void ABaseEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UE_LOG(LogTemp, Display, TEXT("%f"), CurrentAttackCooldown);
	if(CurrentAttackCooldown >= 0)
	{
		CurrentAttackCooldown -= DeltaSeconds;
	}
}

void ABaseEnemy::Attack()
{
	CurrentAttackCooldown = AttackCooldown;
}


