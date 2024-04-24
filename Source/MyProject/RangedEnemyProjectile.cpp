// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedEnemyProjectile.h"

#include "BaseCharacter.h"
#include "BaseEnemy.h"
#include "PlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"

// Sets default values
ARangedEnemyProjectile::ARangedEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
}

// Called when the game starts or when spawned
void ARangedEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &ARangedEnemyProjectile::OnOverlapBegin);
	
}

// Called every frame
void ARangedEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangedEnemyProjectile::OnOverlapBegin(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ProjectileOwner == nullptr)
	{
		Destroy();
		return;
	}
	
	if(APlayerCharacter* PlayerHit = Cast<APlayerCharacter>(SweepResult.GetActor()))
	{
		if(ProjectileOwner != nullptr){
			PlayerHit->TakeDamage(DamageDealt, FDamageEvent(), ProjectileOwner->GetInstigatorController(), this);
		}
	}

	//Kan vara det som krashar?
	if(Cast<ABaseEnemy>(SweepResult.GetActor()))
	{
		return;
	}
	Destroy();
}

void ARangedEnemyProjectile::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	ProjectileOwner = NewOwner;
}

