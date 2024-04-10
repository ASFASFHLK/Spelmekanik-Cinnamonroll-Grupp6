// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HealthComp.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComp = CreateDefaultSubobject<UHealthComp>(TEXT("Character Comp"));
	
}

// Called when the game starts or when spawned	
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::MoveForward(float Value)
{
	// prevents nullptr
	if (Controller == nullptr or Value == 0.0f)
	{
		return;
	}

	// find out which direction is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
		
	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value * MovementSpeed);
	
}

void ABaseCharacter::MoveSides(float Value)
{
	// prevents nullptr
	if (Controller == nullptr or Value == 0.0f)
	{
		return; 
	}
	
	// find out which direction is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
		
	// get right vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
	// add movement in that direction
	AddMovementInput(Direction, Value * MovementSpeed);
	
}

void ABaseCharacter::MoveForwardAxis(float Value)
{

	
}

void ABaseCharacter::MoveSidesAxis(float Value)
{

	
}



// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Movement
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSides"), this, &ABaseCharacter::MoveSides);

	// jump
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ABaseCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this , &ACharacter::StopJumping);
	
}

