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

	CapsuleComponent->SetCapsuleSize(15.0f,40.0f );
	
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp Mesh"));
	PickUpMesh->SetupAttachment(RootComponent);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void APowerup::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(!PickUpEffect)
	{
		return; 
	}
	
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if(Player)
	{
		EffectHandle = Player->AddPassiveEffect(PickUpEffect);
		UE_LOG(LogTemp, Warning, TEXT("Granted player an effect"))
		
		if(!ShouldRespawn)
		{
			Destroy();
		}
	}
	
}

