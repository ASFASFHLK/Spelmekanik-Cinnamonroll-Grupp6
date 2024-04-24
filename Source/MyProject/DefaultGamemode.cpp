// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGamemode.h"

#include "Blueprint/UserWidget.h"

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

void ADefaultGamemode::StartShopPhase_Implementation()
{
	
}


