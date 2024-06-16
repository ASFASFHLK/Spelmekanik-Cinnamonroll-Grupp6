// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"

#include "CheckPointKillBox.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnGate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = SpawnGate;
	
	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
	SpawnPoint->bHiddenInGame = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere")); 
	SphereComponent->SetSphereRadius(110.0f);
	SphereComponent->SetupAttachment(SpawnPoint);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnOverlapBegin);
}

void ACheckPoint::SetRespawnManager( ACheckPointKillBox* Manager)
{
	if(Manager !=nullptr)
	{
		RespawnManager = Manager; 
	}
}

void ACheckPoint::RespawnEvent_Implementation()
{
}

void ACheckPoint::StartRespawnSpawnEvent()
{
	RespawnEvent();
}

void ACheckPoint::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(HasBeenActivated)
	{
		return;
	}
	
	if(Cast<APlayerCharacter>(OtherActor))
	{
		RespawnManager->SetCurrentRespawnPoint(this);
		UE_LOG(LogTemp, Warning, TEXT("Check point set"))
		if(!CanBeReactivated)
		{
			HasBeenActivated = true;
		}
	}
	
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ACheckPoint::GetSpawnPointLocation() const
{
	return SpawnPoint->GetComponentLocation();
}

FRotator ACheckPoint::GetSpawnerRotator() const
{
	return SpawnPoint->GetComponentRotation(); 
}

