// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Squad.h"
#include "GameFramework/Actor.h"
#include "SquadManager.generated.h"

class ASquad;

UCLASS()
class MYPROJECT_API ASquadManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquadManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool AssignNewPartner(ABaseEnemy* EnemyToAssign, ASquad* OriginalSquad);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	int NumberOfSquads;

	UPROPERTY(VisibleAnywhere, Category = "Squad")
	TArray<ASquad*> MySquads;

	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	TSubclassOf<ASquad> SquadType;

	void SpawnSquads();

};
