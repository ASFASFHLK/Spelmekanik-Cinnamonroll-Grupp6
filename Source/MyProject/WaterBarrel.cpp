// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterBarrel.h"

#include "BaseEnemy.h"

void AWaterBarrel::Explode(AController* EventInstigator)
{
	
	Super::Explode(EventInstigator);

	for(int i = 0; i < CharactersHit.Num(); i++)
	{
		CharactersHit[i]->ApplyStun(TimeStunned);
		
	}
}
