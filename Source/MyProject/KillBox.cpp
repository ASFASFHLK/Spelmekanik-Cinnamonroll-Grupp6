// Fill out your copyright notice in the Description page of Project Settings.


#include "KillBox.h"

#include "BaseEnemy.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"

void AKillBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);
	if (Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("I have been killed by the big mean killbox"));
		const bool Discard = Enemy->OnDeath.ExecuteIfBound();
		Enemy->SetActorEnableCollision(false);
		Enemy->HasDied();
		return;
	}
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if(Player)
	{
		// call reset pos func
		Player->TeleportTo(RespawnPos, Player->GetActorRotation());
	}

	
}

// Sets default values
AKillBox::AKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKillBox::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AKillBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




