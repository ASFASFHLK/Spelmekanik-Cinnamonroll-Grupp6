// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGamemode.h"

#include "Enemy_Spawner.h"
#include "PlayerCharacter.h"
#include "SquadManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ADefaultGamemode::EndGame(bool PlayerWin)
{
	if(PlayerWin)
	{
		StartShopPhase();
	}else
	{
		UUserWidget* LoserWidget = CreateWidget<UUserWidget>(GetWorld(),LoseScreen);
		LoserWidget->AddToViewport();
	}
}

void ADefaultGamemode::StartNextWave()
{
	if(SpawnerRef == nullptr)
	{
		SpawnerRef = Cast<AEnemy_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy_Spawner::StaticClass()));
		if(SpawnerRef == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("There should be an Enemy_Spawner in the scene"))
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Startar"));
	//SpawnerRef->IncreaseScaling(EnemyScaling);
	SpawnerRef->StartNextWave();
	if(!bFirstWave)
	{
		APlayerCharacter* Player =Cast<APlayerCharacter>( UGameplayStatics::GetPlayerCharacter(this,0));
		Player->TeleportTo(FVector(-4090,-2050, 4500),Player->GetActorRotation());
	}
	
}

void ADefaultGamemode::StartOptionsMenu_Implementation()
{
}

void ADefaultGamemode::StartShopPhase_Implementation()
{
	
}


