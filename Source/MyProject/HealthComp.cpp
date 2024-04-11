// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComp.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealthComp::SetHealthModifier(int NewHealthModifier)
{
	HealthModifier = NewHealthModifier;
	// Makes sure that CurrentHp Can never be bigger than MaxHealth
	if(CurrentHealth <= GetMaxHealth())
	{
		return;
	}
	CurrentHealth = GetMaxHealth();
}

int32 UHealthComp::GetMaxHealth() const
{
	return MaxHealth + HealthModifier;
}

int UHealthComp::GetCurrentHealth() const
{
	return CurrentHealth;
}

bool UHealthComp::TakeDamage(int DamageToTake)
{
	CurrentHealth = CurrentHealth - DamageToTake;
	UE_LOG(LogTemp, Display, TEXT("Damage Taken %i"), DamageToTake)
	UE_LOG(LogTemp, Display, TEXT("Current Health %i"), CurrentHealth)
	return CurrentHealth <= 0;
}

float UHealthComp::GetHealthPercentage() const
{
	//UE_LOG(LogTemp, Display, TEXT("MAxHealth %i"), GetMaxHealth())
	float procent = static_cast<float>(CurrentHealth / (float)GetMaxHealth());
	//UE_LOG(LogTemp, Display, TEXT("Health procetn %f"), procent)
	return procent;
}

void UHealthComp::SetMaxHealth(int32 NewMaxHealthValue)
{
	MaxHealth = NewMaxHealthValue;
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = GetMaxHealth();
	// ...
}


// Called every frame
void UHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

