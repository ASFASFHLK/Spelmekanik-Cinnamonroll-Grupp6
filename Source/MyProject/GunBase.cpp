// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "BaseEnemy.h"
#include "PlayerCharacter.h"
#include "RangedEnemyProjectile.h"
#include "RivetAttributeSet.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	CHaracterRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(CHaracterRef == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Can not find player"))
	}
	if(GetOwner())
	{
		GetOwner<APlayerCharacter>()->SetGun(this);
		PlayerController = Cast<APlayerController>(GetOwner<APlayerCharacter>()->GetController());
		SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();	
		SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation()+ SpawnRotation.RotateVector(MuzzleOffset);
		QueryParams.AddIgnoredActor(PlayerController->GetPawn());
	}
}

void AGunBase::GunHit_Implementation()
{
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentRifleShotCooldown -= DeltaTime;
}

void AGunBase::Shoot()
{
	//UE_LOG(LogTemp, Warning, TEXT("Trying to shoot"));
	if(this == nullptr || GetOwner<APlayerCharacter>()->GetController() == nullptr){
		return;
	}
	UseShotGun();
}


void AGunBase::ShotGunShot()
{
	//UE_LOG(LogTemp, Warning, TEXT("I shot a shotgunshot"));
	if(World)
	{
		bCanShoot = false;
		SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		GunFired(); // juni
		bool EventCalled = false;
		int const DamageAttribute = CHaracterRef->GetAttributeSet()->GetDamage();
		for (int i = 0; i < Pellets; ++i)
		{
			FHitResult HitResult;
			FRotator Spread = SpawnRotation;
			const float XSpread = FMath::RandRange(ShotgunSpreadMin, ShotgunSpreadMax);
			const float YSpread = FMath::RandRange(ShotgunSpreadMin, ShotgunSpreadMax);
			Spread.Yaw += XSpread;
			Spread.Pitch += YSpread;
			World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams);
			//DrawDebugLine(World, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), FColor::Red, false, 1.5f);
			if(HitResult.GetActor())
			{
				//UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
				HitResult.GetActor()->TakeDamage(DamageAttribute, FDamageEvent(),CHaracterRef->GetController(), this );
				if(ShotSound){
					UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
				}
				ShotgunHitResult = HitResult;
				ShotGunHitLocation = HitResult.Location;
				GunHit(); // juni
				if(!EventCalled)
				{
					if(HitResult.GetActor()->GetClass()->IsChildOf(ABaseEnemy::StaticClass())) // Should be replaced with a tag check as it is way cheaper 
					{
						AnimatedOnHit();
						EventCalled = true; 
					}
	
				}
				
			}
		}
	}
}

void AGunBase::LaserShot()
{
	//UE_LOG(LogTemp, Warning, TEXT("I shot a lazershot"));
	if(World)
	{
		FHitResult HitResult;
		SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * ShotDistance), FColor::Red, false, 0.02f);
		GunFired(); 
		if(HitResult.GetActor())
		{
			//UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
			HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetOwner<APlayerCharacter>()->GetController(), this );
			if(ShotSound){
				UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
			}
			GunHit();
		}
	}
}

void AGunBase::ReloadShotGunShot()
{
	bCanShoot = true;
}

void AGunBase::ReloadPunch()
{
	bCanHit = true;
}

void AGunBase::Punch()
{
	if(!bCanHit)
	{
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &AGunBase::ReloadShotGunShot, ShotGunReloadTime, false);
	SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	const TArray<AActor*> ActorsToIgnore = {GetOwner()};

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(this, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * PunchDistance), PunchRadius, UEngineTypes::ConvertToTraceType(ECC_Pawn), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);
	for (FHitResult Result : HitResults)
	{
		if(ABaseCharacter* ActorHit = Cast<ABaseCharacter>(Result.GetActor()))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s just got punched"), *ActorHit->GetName());
			ActorHit->Parry();
			ActorHit->TakeDamage(Damage, FDamageEvent(), GetOwner<APlayerCharacter>()->GetController(), this);
		}
		if(const ARangedEnemyProjectile* ActorHit = Cast<ARangedEnemyProjectile>(Result.GetActor()))
		{
			FVector OutVelocity;
			UGameplayStatics::SuggestProjectileVelocity_CustomArc(this,OutVelocity, ActorHit->GetActorLocation(), ActorHit->GetActorLocation() + (GetOwner()->GetActorRotation().Vector() * LaunchDistance));
			ActorHit->ProjectileMovement->Velocity = OutVelocity;
		}
	}
	
	
	// UKismetSystemLibrary::SphereTraceSingle(this,SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * PunchDistance), 50, UEngineTypes::ConvertToTraceType(ECC_Pawn),false, ActorsToIgnore, EDrawDebugTrace::ForDuration,HitResult,true, FColor::Red, FColor::Green, 1.5f);
	//
	// if(ABaseCharacter* ActorHit = Cast<ABaseCharacter>(HitResult.GetActor()))
	// {
	// 	ActorHit->TakeDamage(Damage, FDamageEvent(), GetOwner<APlayerCharacter>()->GetController(), this);
	// }
	bCanHit = false;
	GetWorld()->GetTimerManager().SetTimer(HitTimerHandle, this, &AGunBase::ReloadPunch, HitCooldown, false);
}

void AGunBase::AnimatedOnHit_Implementation()
{
}

void AGunBase::UseShotGun()
{
	//UE_LOG(LogTemp, Warning, TEXT("trying to shoot"));
	if(bCanShoot)
	{
		ShotGunShot();
		bCanHit = false;
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &AGunBase::ReloadShotGunShot, ShotGunReloadTime, false);
		GetWorld()->GetTimerManager().SetTimer(HitTimerHandle, this, &AGunBase::ReloadPunch, HitCooldown, false);
	}
	
	// if(BurstCheck == 0 && !bCanceledShot) //crashed after this was added
	// {
	// 	++BurstCheck;
	// 	UE_LOG(LogTemp, Warning, TEXT("First shot = %i"), BurstCheck);//crash
	// 	ShotGunShot();
	// }
	// if(GetWorld()->GetTimerManager().IsTimerPaused(BurstTimerHandle) && !bCanceledShot)
	// {
	// 	GetWorld()->GetTimerManager().UnPauseTimer(BurstTimerHandle);
	// 	GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &AGunBase::ShotGunShot, BurstTime, false);
	// 	++BurstCheck;
	// 	UE_LOG(LogTemp, Warning, TEXT("BurstCheckt = %i"), BurstCheck);
	// }
	// else if(BurstCheck < Bursts - 1 && !bCanceledShot)
	// {
	// 	++BurstCheck;
	// 	UE_LOG(LogTemp, Warning, TEXT("BurstChecknormal = %i"), BurstCheck);
	// 	GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &AGunBase::ShotGunShot, BurstTime, false);
	// }
}
void AGunBase::Reload()
{
	bCanShoot = true;
	BurstCheck = 0;
	//UE_LOG(LogTemp, Warning, TEXT("Can shoot"));
}

void AGunBase::GunFired_Implementation()
{
	
}
