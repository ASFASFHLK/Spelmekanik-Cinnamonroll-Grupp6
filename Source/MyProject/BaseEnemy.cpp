// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Kismet/GameplayStatics.h"


void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentTarget = UGameplayStatics::GetPlayerCharacter(this, 0);
}
