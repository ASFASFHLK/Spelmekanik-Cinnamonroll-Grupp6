// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPointKillBox.h"
#include "CheckPoint.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckPointKillBox::ACheckPointKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckPointKillBox::OnBoxBeginOverlap);
}

int ACheckPointKillBox::GetAmountOfCheckPointsInTheLevel() const
{
	return RespawnPoints.Num();
}

void ACheckPointKillBox::SetCurrentRespawnPoint(ACheckPoint* Point)
{
	if(Point != nullptr)
	{
		if(Point == RespawnPoint)
		{
			return;
		}
		
		if(!ActivatedCheckPoints.Contains(Point)){
			ActivatedCheckPoints.Add(Point);
		}
		
		if(RespawnPoint != nullptr)
		{
			RespawnPoint->StartRespawnPointDisabledEvent();
			RespawnPoint->SetIsEnabled(false);
		}
		RespawnPoint = Point; 
	}
}

void ACheckPointKillBox::PlayerRespawning_Implementation()
{
}

bool ACheckPointKillBox::CheckIfAllCheckPointsHaveBeenActivated() const
{
	return ActivatedCheckPoints.Num() == RespawnPoints.Num(); 
}

int ACheckPointKillBox::GetAmountOfActivatedCheckPoints() const
{
	return ActivatedCheckPoints.Num(); 
}

// Called when the game starts or when spawned
void ACheckPointKillBox::BeginPlay()
{
	Super::BeginPlay();
	GetAllRespawnPointsInTheScene();
	FindPlayerStart();
}

void ACheckPointKillBox::GetAllRespawnPointsInTheScene()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckPoint::StaticClass(), FoundActors);

	for( AActor* Actor : FoundActors)
	{
		if(ACheckPoint* CheckPoint = Cast<ACheckPoint>(Actor))
		{
			CheckPoint->SetRespawnManager(this);
			RespawnPoints.Add(CheckPoint);
		}
	}
}

void ACheckPointKillBox::FindPlayerStart()
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);

	if(FoundActors.Num() < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find the PlayerStart"));
	}
	PlayerStart = Cast<APlayerStart>(FoundActors.Top());
	if(PlayerStart == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not cast the aplayerstart "))
	}
}

// Called every frame
void ACheckPointKillBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPointKillBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if(Player)
	{
		PlayerRespawning();
		if(RespawnPoint == nullptr)
		{
			if(PlayerStart!= nullptr)
			{
				Player->TeleportTo(PlayerStart->GetCapsuleComponent()->GetComponentLocation(),
				PlayerStart->GetCapsuleComponent()->GetComponentRotation());
			}
			// hard coded  default or something 
			return; 
		}
		
		Player->TeleportTo(RespawnPoint->GetSpawnPointLocation(), RespawnPoint->GetActorRotation());
		RespawnPoint->StartRespawnSpawnEvent();
	}
}


