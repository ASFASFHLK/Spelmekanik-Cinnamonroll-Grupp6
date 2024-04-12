// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBarrel.h"
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
	const FVector Start = GetActorUpVector() + GetActorLocation();
	const FVector End = GetActorUpVector() * Height + GetActorLocation();
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;

	UGameplayStatics::ApplyRadialDamage(this, DamageDealt, GetActorLocation(),
		ExplosionRadius,DamageType,ActorsToIgnore, this, EventInstigator,true, ECC_Pawn);

	DrawDebugSphere(GetWorld(),GetActorLocation(),ExplosionRadius,12,FColor::Red,true,5.f);
	
	

	Destroy();
}

float ABaseBarrel::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(HealthComp->TakeDamage(DamageAmount))
	{
		Explode(EventInstigator);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

// Called every frame
void ABaseBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

