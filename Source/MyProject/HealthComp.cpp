// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComp.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

FString UHealthComp::GetHealthAsText() const
{
	const std::string StringRef = (std::to_string(GetCurrentHealth()) + "/" + std::to_string(GetMaxHealth()));
	const FString ReturnFString(StringRef.c_str());
	return ReturnFString;
}

void UHealthComp::SetHealthToMax()
{
	CurrentHealth = MaxHealth; 
}

void UHealthComp::SetHealthModifier(int NewHealthModifier)
{
	HealthModifier = NewHealthModifier;
	// Makes sure that CurrentHp Can never be bigger than MaxHealth
	if(CurrentHealth <= MaxHealth)
	{
		return;
	}
	CurrentHealth = MaxHealth;
}

void UHealthComp::ResetHealth()
{
	SetHealthToMax();
}

int32 UHealthComp::GetMaxHealth() const
{
	return MaxHealth;
}

int UHealthComp::GetCurrentHealth() const
{
	return CurrentHealth;
}

bool UHealthComp::TakeDamage(const int DamageToTake)
{
	
	CurrentHealth =  FMath::Clamp(CurrentHealth, 0.f, CurrentHealth -DamageToTake);
	return CurrentHealth <= 0;
}

float UHealthComp::GetHealthPercentage() const
{
	if(MaxHealth == 0)
	{
		return  0.0;
	}
	return CurrentHealth/static_cast<float>(MaxHealth);
}

void UHealthComp::SetMaxHealth(const int32 NewMaxHealthValue)
{
	MaxHealth = NewMaxHealthValue;
}


void UHealthComp::AddHealth(const int HealthToAdd)
{

	CurrentHealth += HealthToAdd;
	
	if(CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth; 
	}
	//UE_LOG(LogTemp, Display, TEXT("%d"), MaxHealth);
}

// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth; 
	
	//CurrentHealth = GetMaxHealth();
	// ...
}


// Called every frame
void UHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

