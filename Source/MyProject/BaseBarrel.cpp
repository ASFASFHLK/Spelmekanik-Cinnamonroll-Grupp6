// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBarrel.h"

// Sets default values
ABaseBarrel::ABaseBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

