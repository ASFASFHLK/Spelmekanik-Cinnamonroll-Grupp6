// Fill out your copyright notice in the Description page of Project Settings.


#include "ModifierComponent.h"

#include "BaseModifier.h"


// Sets default values for this component's properties
UModifierComponent::UModifierComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UModifierComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Modifiers.SetNum(MaxModifiersAllowed);
	for(int i = 0; i < MaxModifiersAllowed; i++)
	{
		Modifiers[i] = nullptr;
	}
}


// Called every frame
void UModifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	
	if(ModifierOne)
	{
		ModifierOne->OnUpdate(DeltaTime);
	}
	if(ModifierTwo)
	{
		ModifierTwo->OnUpdate(DeltaTime);
	}


}

void UModifierComponent::ChangeModifiers(TSubclassOf<ABaseModifier> NewModifier, const int ModifierPlace)
{
	if(Modifiers.Num() < ModifierPlace)
	{
		UE_LOG(LogTemp, Warning, TEXT("The maximum amount of modifers have been reached"));
		return;
	}
	if(Modifiers[ModifierPlace] == nullptr)
	{
		ABaseModifier* CreatedModifier = NewObject<ABaseModifier>(this, NewModifier);
		CreatedModifier->OnAdded();
		Modifiers[ModifierPlace] = CreatedModifier;
		return;
	}
	Modifiers[ModifierPlace]->OnRemoved();
	Modifiers[ModifierPlace]->Destroy();
	
	ABaseModifier* CreatedModifier = NewObject<ABaseModifier>(this, NewModifier);
	CreatedModifier->OnAdded();
	Modifiers[ModifierPlace] = CreatedModifier;
	return;
	
	switch(ModifierPlace)
	{
	case 1:
		if(ModifierOne)
		{
			ModifierOne->OnRemoved();
		}
		ModifierOne = NewObject<ABaseModifier>(this, NewModifier);
		ModifierOne->OnAdded();
		break;

	case 2:
		if(ModifierTwo)
		{
			ModifierTwo->OnRemoved();
		}
		ModifierTwo = NewObject<ABaseModifier>(this, NewModifier);
		ModifierTwo->OnAdded();
		break;
		
	default:
		UE_LOG(LogTemp, Warning, TEXT("Invalid modifier placement"));
		break;
	}
}

void UModifierComponent::SetMaxModifiersAllowed(int NewValue)
{
	if(NewValue < MaxModifiersAllowed)
	{
		UE_LOG(LogTemp, Display, TEXT("I will remove all modifers that excided the maximum amount allowed"));
		for(int i = MaxModifiersAllowed -1; i > NewValue; i--)
		{
			Modifiers[i]->OnRemoved();
			Modifiers[i]->Destroy();
		}
	}
	MaxModifiersAllowed = NewValue;
	Modifiers.SetNum(MaxModifiersAllowed);
}










