// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveAbilityDash.h"

#include "BaseCharacter.h"

void UActiveAbilityDash::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Warning, TEXT("Dash begun"))
	
	ABaseCharacter* Character = Cast<ABaseCharacter>(ActorInfo->AvatarActor);
	if(Character)
	{
		Dash(Character);
	}
}

void UActiveAbilityDash::Dash(ABaseCharacter* Character)
{
	const FVector ForwardDirection = Character->GetActorRotation().Vector();
	Character->LaunchCharacter(ForwardDirection * DashDistance, true, true);
	Timer = DashCoolDown;
	IsDashing = true;
	
}
