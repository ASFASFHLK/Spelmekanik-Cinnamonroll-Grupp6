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
	Modifiers.SetNum(MaxModifiersAllowed);// sets the default size 
	
	// sets up the default modifer array 
}


void UModifierComponent::AddNewModifier(const TSubclassOf<ABaseModifier> NewModifier, const int ModifierPlace, TArray<ABaseModifier*>& List)
{
	ABaseModifier* CreatedModifier = NewObject<ABaseModifier>(this, NewModifier);
	CreatedModifier->OnAdded();
	UE_LOG(LogTemp, Warning, TEXT("Added a Modifer with the name %ls"), *CreatedModifier->GetName());
	List[ModifierPlace] = CreatedModifier;
	ModifierUpdates.AddDynamic(CreatedModifier, &ABaseModifier::OnUpdate);
}

void UModifierComponent::RemoveModifer(const int ModifierPlace, TArray<ABaseModifier*>& List)
{
	// might be a bit redundant 
	ABaseModifier* Target = Modifiers[ModifierPlace];
	
	if(Target == nullptr)
	{
		return;
	}
	
	Target->OnRemoved();
	Target->Destroy();
	ModifierUpdates.RemoveDynamic(Target, &ABaseModifier::OnUpdate);
}

// Called every frame
void UModifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ModifierUpdates.Broadcast(DeltaTime); 
}

void UModifierComponent::ChangeModifiers(TSubclassOf<ABaseModifier> NewModifier, const int ModifierPlace)
{
	if(MaxModifiersAllowed < ModifierPlace)
	{
		//UE_LOG(LogTemp, Warning, TEXT("The maximum amount of modifers have been reached %i"), Modifiers.Num());
		return;
	}
	if(Modifiers[ModifierPlace] != nullptr)
	{
		RemoveModifer(ModifierPlace, Modifiers);
	}
	AddNewModifier(NewModifier, ModifierPlace, Modifiers);
}

void UModifierComponent::SetMaxModifiersAllowed(int NewValue)
{
	if(NewValue < MaxModifiersAllowed)
	{
		UE_LOG(LogTemp, Display, TEXT("I will remove all modifers that excided the maximum amount allowed"));
		for(int i = MaxModifiersAllowed -1; i > NewValue; i--)
		{
			RemoveModifer(i, Modifiers);
		}
	}
	Modifiers.SetNum(MaxModifiersAllowed);
	MaxModifiersAllowed = NewValue;
}

void UModifierComponent::SetUp()
{
	DefaultModifiers_Internal.SetNum(DefaultModifiers.Num());
	int i = 0;
	for (const TSubclassOf<ABaseModifier> DefaultMod : DefaultModifiers)
	{
		AddNewModifier(DefaultMod, i, DefaultModifiers_Internal);
		i++;
	}
}










