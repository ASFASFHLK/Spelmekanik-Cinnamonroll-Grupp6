// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBarrel.h"

#include "BaseCharacter.h"
#include "HealthComp.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseBarrel::ABaseBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("Health Comp"));

}

// Called when the game starts or when spawned
void ABaseBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseBarrel::Explode(AController* EventInstigator)
{
	const TArray<AActor*> ActorsToIgnore;
	
	Exploded = true;

	const FVector End = GetActorLocation() + FVector(ExplosionRadius,ExplosionRadius,0);
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(ExplosionRadius);
	
	GetWorld()->SweepMultiByChannel(HitResults,GetActorLocation(), End,
		FQuat::Identity, ECC_Pawn,Sphere);

	for(int i = 0; i<HitResults.Num(); i++)
	{
		if(HitResults[i].GetActor()->IsA(ABaseCharacter::StaticClass()))
		{
			ABaseCharacter* Target = Cast<ABaseCharacter>(HitResults[i].GetActor());
			Target->TakeDamage(DamageDealt,FDamageEvent(),EventInstigator,this);
			CharactersHit.Add(Target);
		}
	}
	DrawDebugSphere(GetWorld(),GetActorLocation(),ExplosionRadius,12,FColor::Red,true,5.f);
	
	
	
}

float ABaseBarrel::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(!Exploded && HealthComp->TakeDamage(DamageAmount))
	{
		Explode(EventInstigator);
		Destroy(); 
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

// Called every frame
void ABaseBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

