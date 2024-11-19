// Fill out your copyright notice in the Description page of Project Settings.


#include "RivetAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "PlayerCharacter.h"


URivetAttributeSet::URivetAttributeSet()
{
}

void URivetAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(URivetAttributeSet, Health);
	DOREPLIFETIME(URivetAttributeSet, Damage);
	DOREPLIFETIME(URivetAttributeSet, Speed);
	DOREPLIFETIME(URivetAttributeSet, Armour);
	DOREPLIFETIME(URivetAttributeSet, MaxHealth);
	DOREPLIFETIME(URivetAttributeSet, JumpCount);
}

void URivetAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	/**	if(Attribute == GetMaxHealthAttribute())
	{
		//AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}**/
}

void URivetAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	return;
	UE_LOG(LogTemp, Warning, TEXT("Effect has happend"))
	Super::PostGameplayEffectExecute(Data);
	const FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	//UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	
	float DeltaValue {0.f};

	if(Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}
	ABaseCharacter* TargetCharacter {nullptr};

	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetCharacter = Cast<ABaseCharacter>(TargetActor);
	}

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		if(TargetCharacter)
		{
			//TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		}
	}
	
}

void URivetAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, Health, OldValue);
}

void URivetAttributeSet::OnRep_Armour(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, Armour, OldValue);
}

void URivetAttributeSet::OnRep_TestHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, TestHealth, OldValue);
}

void URivetAttributeSet::OnRep_TestMaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, TestMaxHealth, OldValue);
}

void URivetAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, MaxHealth, OldValue);
}

void URivetAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, Damage, OldValue);
}

void URivetAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, Speed, OldValue);
}

void URivetAttributeSet::OnRep_JumpCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, JumpCount, OldValue);
}
void URivetAttributeSet::OnRep_JumpHeight(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, JumpHeight, OldValue);
}

void URivetAttributeSet::OnRep_ExplosionRadius(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, ExplosionRadius, OldValue);
}

void URivetAttributeSet::OnRep_ExplosionChargeRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, ExplosionChargeRate, OldValue);
}

void URivetAttributeSet::OnRep_ExtraCredits(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, ExtraCredits, OldValue);
}

void URivetAttributeSet::OnRep_ChargeRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URivetAttributeSet, ChargeRate, OldValue);
}

void URivetAttributeSet::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
                                                     const FGameplayAttributeData& MaxAttribute, float NewMaxValue,
                                                     const FGameplayAttribute& AffectedAttributeProperty) const
{
	return;
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if(!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		const float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue/ CurrentMaxValue)-CurrentValue : NewMaxValue;
		AbilityComp-> ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
		
	}
	
}
