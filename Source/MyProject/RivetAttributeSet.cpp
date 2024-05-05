// Fill out your copyright notice in the Description page of Project Settings.


#include "RivetAttributeSet.h"
#include "Net/UnrealNetwork.h"

URivetAttributeSet::URivetAttributeSet()
{
}

void URivetAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(URivetAttributeSet, Health);
	DOREPLIFETIME(URivetAttributeSet, Damage);
	DOREPLIFETIME(URivetAttributeSet, Speed);
}

void URivetAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, Health, OldValue);
}

void URivetAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, Damage, OldValue);
}

void URivetAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, Speed, OldValue);
}
