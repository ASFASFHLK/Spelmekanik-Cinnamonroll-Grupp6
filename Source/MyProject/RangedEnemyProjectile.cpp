// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyProjectile.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"

// Sets default values
ARangedEnemyProjectile::ARangedEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARangedEnemyProjectile::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("BLRJAR"));
	Super::BeginPlay();
	
}

// Called every frame
void ARangedEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangedEnemyProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	FVector normalImpulse, const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Display, TEXT("asdasdasd"));
	//Get a reference as to who spawned the actor
	AActor* projectileOwner = GetOwner();

	if(AActor* ActorHit = HitResult.GetActor())
	{
		ActorHit->TakeDamage(DamageDealt, FDamageEvent(), projectileOwner->GetInstigatorController(), this);
		
	}
	if (otherActor != NULL && otherActor != this && otherActor != projectileOwner) {
		
		Destroy();
	}
}

