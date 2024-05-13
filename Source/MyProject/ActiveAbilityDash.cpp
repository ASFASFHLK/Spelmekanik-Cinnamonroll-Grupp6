// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveAbilityDash.h"

#include "BaseCharacter.h"

void UActiveAbilityDash::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Warning, TEXT("Dash begun"))

	if(Character == nullptr){
		Character = Cast<ABaseCharacter>(ActorInfo->AvatarActor);
    }
	if(Character)
	{
		Dash();
	}
}

void UActiveAbilityDash::Dash()
{
	//const FVector ForwardDirection = Character->GetActorRotation().Vector();
	FVector MoveDirection = Character->GetVelocity();
	MoveDirection.Z = 0.0f;
	MoveDirection = MoveDirection.GetSafeNormal();
	Character->LaunchCharacter(MoveDirection * DashDistance, true, false);

	
}
