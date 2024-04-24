// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "PlayerCharacter.h"
#include "Engine/DamageEvents.h"
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
	if(GetOwner())
	{
		GetOwner<APlayerCharacter>()->SetGun(this);
	}
	Super::BeginPlay();
	
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunBase::Shoot()
{
	if(this == nullptr || GetOwner<APlayerCharacter>()->GetController() == nullptr){
		return;
	}
	switch (GunType)
	{
	case 0:
		if(bRifleShouldShoot)
		{
			RifleShot();
			bRifleShouldShoot = false;
		}
		if(!bRifleShouldShoot)
		{
			bRifleShouldShoot = true;
		}
		break;
	case 1:
		if(bCanShoot)
		{
			UseShotGun();
		}
		break;
	case 2:
		LaserShot();
		break;
	default: UE_LOG(LogTemp, Warning, TEXT("Not correct GunType"));
	}
}

void AGunBase::CancelShot()
{
	if(GetWorld())
 	{
 		if(!bCanceledShot)
 		{
 			bCanceledShot = true;
 			BurstCheck = 0;
 			GetWorld()->GetTimerManager().PauseTimer(BurstTimerHandle); 
 			GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &AGunBase::Reload, ReloadTime, false);
 		}
 	}
}

void AGunBase::RifleShot()
{
	UE_LOG(LogTemp, Warning, TEXT("I shot a rifleshot"));
	UWorld* const World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner<APlayerCharacter>()->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		FRotator Spread = SpawnRotation;
		double XSpread = FMath::RandRange(-5.0f, 5.f);
		double YSpread = FMath::RandRange(-5.0f, 5.f);
		Spread.Yaw += XSpread;
		Spread.Pitch += YSpread;
		QueryParams.AddIgnoredActor(PlayerController->GetPawn());
		World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), FColor::Red, false, 1.0f);
		if(HitResult.GetActor())
		{
			UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
			HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetOwner<APlayerCharacter>()->GetController(), this );
			if(ShotSound){
				UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
			}
		}
	}
}

void AGunBase::ShotGunShot()
{
	UE_LOG(LogTemp, Warning, TEXT("I shot a shotgunshot"));
	if(UWorld* const World = GetWorld())
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner<APlayerCharacter>()->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		for (int i = 0; i < Pellets; ++i)
		{
			FRotator Spread = SpawnRotation;
			double XSpread = FMath::RandRange(-15.0f, 15.f);
			double YSpread = FMath::RandRange(-15.0f, 15.f);
			Spread.Yaw += XSpread;
			Spread.Pitch += YSpread;
			QueryParams.AddIgnoredActor(PlayerController->GetPawn());
			World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), FColor::Red, false, 1.5f);
			if(HitResult.GetActor())
			{
				UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
				HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetOwner<APlayerCharacter>()->GetController(), this );
				if(ShotSound){
					UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
				}
			}
		}
	}
	bCanShoot = false;
}

void AGunBase::LaserShot()
{
	UE_LOG(LogTemp, Warning, TEXT("I shot a lazershot"));
	if(UWorld* const World = GetWorld())
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner<APlayerCharacter>()->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(PlayerController->GetPawn());
		World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * ShotDistance), FColor::Red, false, 0.01f);
		if(HitResult.GetActor())
		{
			UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
			HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetOwner<APlayerCharacter>()->GetController(), this );
			if(ShotSound){
				UGameplayStatics::PlaySoundAtLocation(World, ShotSound, SpawnLocation, FRotator::ZeroRotator);
			}
		}
	}
}

void AGunBase::ReloadShotGunShot()
{
	bCanShoot = true;
}

void AGunBase::ChangeGunType()
{
	if(GunType >= 3)
	{
		GunType = 0;
	}
	else
	{
		++GunType;
	}
}

void AGunBase::UseShotGun()
{
	ShotGunShot();
	GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &AGunBase::ReloadShotGunShot, ShotGunReloadTime, false);
	
	// UE_LOG(LogTemp, Warning, TEXT("I set off a timer"));
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
	UE_LOG(LogTemp, Warning, TEXT("Can shoot"));
}
