// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComp.h"

#include "BaseCharacter.h"
#include "RivetAttributeSet.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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
	return AttributeSet->GetMaxHealth();
}

int UHealthComp::GetCurrentHealth() const
{
	return AttributeSet->GetHealth();
}

bool UHealthComp::TakeDamage(const int DamageToTake)
{
	const float Health = AttributeSet->GetHealth();
	AttributeSet->SetHealth(FMath::Clamp(Health, 0.f, Health -DamageToTake));;
	return AttributeSet->GetHealth() <= 0;
}

float UHealthComp::GetHealthPercentage() const
{
	if(AttributeSet->GetMaxHealth() == 0)
	{
		return  0.0;
	}
	return AttributeSet->GetHealth()/AttributeSet->GetMaxHealth();
}

void UHealthComp::SetMaxHealth(const int32 NewMaxHealthValue)
{
	MaxHealth = NewMaxHealthValue;
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();
	const ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwner());
	if(Character != nullptr)
	{
		AttributeSet = Character->GetAttributeSet();
		if(AttributeSet->GetHealth() > AttributeSet->GetMaxHealth())
		{
		AttributeSet->SetHealth(AttributeSet->GetMaxHealth());	
		}
		
		//AttributeSet->SetHealth(0);
		//AttributeSet->SetMaxHealth(0);
	}
	
	//CurrentHealth = GetMaxHealth();
	// ...
}


// Called every frame
void UHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

