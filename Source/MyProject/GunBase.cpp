// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "K2Node_DoOnceMultiInput.h"
#include "PlayerCharacter.h"
#include "RangedEnemyProjectile.h"
#include "SWarningOrErrorBox.h"
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
	if(GetOwner())
	{
		GetOwner<APlayerCharacter>()->SetGun(this);
		PlayerController = Cast<APlayerController>(GetOwner<APlayerCharacter>()->GetController());
		SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();	
		SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation()+ SpawnRotation.RotateVector(MuzzleOffset);
		QueryParams.AddIgnoredActor(PlayerController->GetPawn());
	}
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentRifleShotCooldown -= DeltaTime;
}

void AGunBase::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to shoot"));
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
	case 3:
		if(bCanHit)
		{
			Punch();
			GetWorld()->GetTimerManager().SetTimer(HitTimerHandle, this, &AGunBase::ReloadPunch, ShotGunReloadTime * 0.8f, false);
		}
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
	if(World && CurrentRifleShotCooldown <= 0)
	{
		CurrentRifleShotCooldown = RifleShotCooldown;// Linus
		SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation()+ SpawnRotation.RotateVector(MuzzleOffset);
		FHitResult HitResult;
		FRotator Spread = SpawnRotation;
		double XSpread = FMath::RandRange(-5.0f, 5.f);
		double YSpread = FMath::RandRange(-5.0f, 5.f);
		Spread.Yaw += XSpread;
		Spread.Pitch += YSpread;
		World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), FColor::Red, false, 1.0f);
		if(HitResult.GetActor())
		{
			//UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
			HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetOwner<APlayerCharacter>()->GetController(), this );
		}
	}
}

void AGunBase::ShotGunShot()
{
	//UE_LOG(LogTemp, Warning, TEXT("I shot a shotgunshot"));
	if(World)
	{
		bCanShoot = false;
		SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		for (int i = 0; i < Pellets; ++i)
		{
			FHitResult HitResult;
			FRotator Spread = SpawnRotation;
			double XSpread = FMath::RandRange(-15.0f, 15.f);
			double YSpread = FMath::RandRange(-15.0f, 15.f);
			Spread.Yaw += XSpread;
			Spread.Pitch += YSpread;
			World->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), ECollisionChannel::ECC_Pawn, QueryParams); DrawDebugLine(World, SpawnLocation, SpawnLocation + (Spread.Vector() * ShotDistance), FColor::Red, false, 1.5f);
			if(HitResult.GetActor())
			{
				//UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
				HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetOwner<APlayerCharacter>()->GetController(), this );
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
		if(HitResult.GetActor())
		{
			//UE_LOG(LogTemp, Display, TEXT("Hit a target %s"),*HitResult.GetActor()->GetName());
			HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(),GetOwner<APlayerCharacter>()->GetController(), this );
			
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

void AGunBase::Punch()
{
	SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	const TArray<AActor*> ActorsToIgnore = {GetOwner()};// might not work
	// FHitResult HitResult;

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(this, SpawnLocation, SpawnLocation + (SpawnRotation.Vector() * PunchDistance), PunchRadius, UEngineTypes::ConvertToTraceType(ECC_Pawn), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FColor::Red, FColor::Green, 1);
	for (FHitResult Result : HitResults)
	{
		if(ABaseCharacter* ActorHit = Cast<ABaseCharacter>(Result.GetActor()))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s just got punched"), *ActorHit->GetName());
			ActorHit->Parry();
			ActorHit->TakeDamage(Damage, FDamageEvent(), GetOwner<APlayerCharacter>()->GetController(), this);
		}
		if(ARangedEnemyProjectile* ActorHit = Cast<ARangedEnemyProjectile>(Result.GetActor()))
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
	//UE_LOG(LogTemp, Warning, TEXT("Can shoot"));
}
