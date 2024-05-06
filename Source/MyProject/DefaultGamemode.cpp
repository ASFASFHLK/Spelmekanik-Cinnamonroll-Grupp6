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

	/*
	if(SquadRef == nullptr)
	{
		SquadRef = Cast<ASquadManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASquadManager::StaticClass()));
		if(SquadRef == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("There should be a SquadManager in the scene"))
			return;
		}
	}
	*/
	SpawnerRef->StartNextWave();
	//SquadRef->StartNextWave();
	APlayerCharacter* Player =Cast<APlayerCharacter>( UGameplayStatics::GetPlayerCharacter(this,0));
	Player->TeleportTo(FVector(-4010,-2600, 4552.0),Player->GetActorRotation());
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
		UE_LOG(LogTemp, Warning, TEXT("AmountToAdd can not be negative"));
		return;
	}
	CurrentAmountOfCredits+= AmountToAdd;
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


void ADefaultGamemode::StartShopPhase_Implementation()
{
	
}


