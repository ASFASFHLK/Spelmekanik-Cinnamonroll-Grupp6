// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseModifier.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseModifier::ABaseModifier(): PlayerCharacter(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseModifier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseModifier::OnAdded()
{
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void ABaseModifier::OnUpdate(float DeltaTime)
{
}

void ABaseModifier::OnRemoved()
{
	Destroy();
}


