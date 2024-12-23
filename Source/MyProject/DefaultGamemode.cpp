// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGamemode.h"

#include "Enemy_Spawner.h"
#include "PlayerCharacter.h"
#include "Squad.h"
#include "Kismet/GameplayStatics.h"

void ADefaultGamemode::EndGame(bool PlayerWin)
{
	if(PlayerWin)
	{
		StartShopPhase();
	}else
	{
		EndGameEvent();
		//UUserWidget* LoserWidget = CreateWidget<UUserWidget>(GetWorld(),LoseScreen);
		//LoserWidget->AddToViewport();
	}
}

void ADefaultGamemode::StartNextWave()
{
	CurrentAmountKilled = 0;
	if(SpawnerRef == nullptr)
	{
		SpawnerRef = Cast<AEnemy_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy_Spawner::StaticClass()));
		if(SpawnerRef == nullptr)
		{
			return;
		}
	}
	
	SpawnerRef->SetScaling(GetCalculatedScaling());
	SpawnerRef->StartNextWave(AmountToSpawn);
	OnSpawnNewWave();
	if(!bFirstWave)
	{
		APlayerCharacter* Player =Cast<APlayerCharacter>( UGameplayStatics::GetPlayerCharacter(this,0));
		Player->TeleportTo(FVector(-4090,-2050, 4500),Player->GetActorRotation());
	}
	
}

void ADefaultGamemode::EndGameEvent_Implementation()
{
}

void ADefaultGamemode::OnSpawnNewWave_Implementation()
{
}

void ADefaultGamemode::StartOptionsMenu_Implementation()
{
}

void ADefaultGamemode::EnemyDied_Implementation()
{
}

void ADefaultGamemode::OnStartNextWave_Implementation()
{
}

void ADefaultGamemode::TriggerNextWaveEvent()
{
	OnStartNextWave();
}

int ADefaultGamemode::GetAmountOfCredits() const
{
	return CurrentAmountOfCredits;
}

void ADefaultGamemode::SetAmountOfCredits(const int AmountToSet)
{
	CurrentAmountOfCredits = AmountToSet;
}

bool ADefaultGamemode::CanAfford(const int PriceToCheck) const
{
	return PriceToCheck <= CurrentAmountOfCredits;
}

void ADefaultGamemode::AddCredits(const int AmountToAdd)
{
	if(AmountToAdd < 0)
	{
		return;
	}
	CurrentAmountOfCredits+= AmountToAdd;
	TotalAmountOfCredits += AmountToAdd;
}

void ADefaultGamemode::ResetCredits()
{
	CurrentAmountOfCredits = 0;
}

void ADefaultGamemode::RemoveCredits(const int AmountToRemove)
{
	if(AmountToRemove < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AmountToRemove can not be negative"));
		return;
	}
	CurrentAmountOfCredits -=AmountToRemove;
}

bool ADefaultGamemode::RemoveIfWeCanAfford(const int PriceToCheck)
{
	if(CanAfford(PriceToCheck))
	{
		RemoveCredits(PriceToCheck);
		return true;
	}
	return false;
}

void ADefaultGamemode::IncreaseAmountOfEnemies(int Amount)
{
	AmountToKill+= Amount;
	AmountToSpawn+= Amount;
}

void ADefaultGamemode::IncreaseEnemiesKilled()
{
	AmountOfKills++;
}

void ADefaultGamemode::OnEnemyKilled()
{
	CurrentAmountKilled++;
	EnemyDied();
	if(Tutorial)
	{
		if(CurrentAmountKilled >= EnemiesToKillInTutorial)
		{
			StartTutorial();
			CurrentAmountKilled = 0;
		}
	}else
	{
		if(CurrentAmountKilled >= AmountToKill)
		{
			//Endgame with player as winner
		
			Cast<ADefaultGamemode>(UGameplayStatics::GetGameMode(this))->EndGame(true);
		
		}
	}
}

void ADefaultGamemode::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	SpawnerRef = Cast<AEnemy_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy_Spawner::StaticClass()));
	SquadRef = Cast<ASquad>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquad::StaticClass()));
}

float ADefaultGamemode::GetCalculatedScaling()
{
	return 1 + (RoundAmount * EnemyScaling);
}

void ADefaultGamemode::StartRoundGameMode_Implementation()
{
}

void ADefaultGamemode::StartTutorial_Implementation()
{
}

void ADefaultGamemode::StartShopPhase_Implementation()
{
	
}


