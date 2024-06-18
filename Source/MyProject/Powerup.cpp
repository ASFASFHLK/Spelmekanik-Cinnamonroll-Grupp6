// Fill out your copyright notice in the Description page of Project Settings.


#include "Powerup.h"

#include "GameplayEffect.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

class APlayerCharacter;
// Sets default values
APowerup::APowerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapusalComp")); 
	RootComponent = CapsuleComponent;

	CapsuleComponent->SetCapsuleSize(30.0f,50.0f );
	
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp Mesh"));
	PickUpMesh->SetupAttachment(RootComponent);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerup::OnOverlapBegin);
	PickUpMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APowerup::ItemPickedUped_Implementation()
{
}

void APowerup::ItemRespawned_Implementation()
{
}

// Called when the game starts or when spawned
void APowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APowerup::SetComponentsActive(const bool State)
{
	CapsuleComponent->SetActive(State);
	PickUpMesh->SetActive(State);
	
	CapsuleComponent->SetVisibility(State);
	PickUpMesh->SetVisibility(State);
	
		
}

// Called every frame
void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsRespawning)
	{
		Accumulator += DeltaTime;
		if(Accumulator > RespawnTime)
		{
			SetComponentsActive(true);
			Accumulator = 0;
			IsRespawning = false;
			ItemRespawned();
		}
	}
	
}

void APowerup::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsRespawning)
	{
		return; 
	}
	
	if(!PickUpEffect)
	{
		return; 
	}
	
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if(Player)
	{
		
		EffectHandle = Player->AddPassiveEffect(PickUpEffect);

		ItemPickedUped();
		if(EffectHandle.IsValid()) 
		{
			Player->UpdateVariables();
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Granted player an effect"))
		
		SetComponentsActive(false);
		
		if(ShouldRespawn)
		{
			IsRespawning = true; 
		}
		else
		{
			Destroy();
		}
	}
	
}

