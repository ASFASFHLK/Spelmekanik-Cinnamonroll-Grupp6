// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerExplosiveProjectile.h"

// Sets default values
APlayerExplosiveProjectile::APlayerExplosiveProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

}

// Called when the game starts or when spawned
void APlayerExplosiveProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerExplosiveProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerExplosiveProjectile::OnOverlapBegin(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ProjectileOwner == nullptr)
	{
		Destroy();
		return;
	}
	Explode();
	
}

void APlayerExplosiveProjectile::DealDamage(ABaseCharacter* Character)
{
}

void APlayerExplosiveProjectile::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}


