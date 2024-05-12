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

FString UHealthComp::GetHealthAsText() const
{
	const std::string StringRef = (std::to_string(GetCurrentHealth()) + "/" + std::to_string(GetMaxHealth()));
	const FString ReturnFString(StringRef.c_str());
	return ReturnFString;
}

void UHealthComp::SetHealthToMax()
{
	AttributeSet->SetHealth(GetMaxHealth());
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

void UHealthComp::ResetHealth()
{
	SetHealthToMax();
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


void UHealthComp::AddHealth(const int HealthToAdd)
{
	const int NewHealth = AttributeSet->GetHealth() + HealthToAdd;
	AttributeSet->SetHealth(NewHealth);
	CurrentHealth = AttributeSet->GetHealth();
	UE_LOG(LogTemp, Display, TEXT("%f"), AttributeSet->GetHealth());
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
		//AttributeSet->SetHealth(AttributeSet->GetMaxHealth());	
		}
		if(AllowHealthCompToSetHealth)
		{
			AttributeSet->SetHealth(MaxHealth);
			AttributeSet->SetMaxHealth(MaxHealth);
		}

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

