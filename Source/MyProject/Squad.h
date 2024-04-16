// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "Squad.generated.h"

class ASquadManager;
class ABaseEnemy;

UCLASS()
class MYPROJECT_API ASquad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SetSquadManager(ASquadManager* SquadManager) {MySquadManager = SquadManager;}
	bool FindSquadMemberToBind(ABaseEnemy* EnemyToFindPartnerFor);
	void FindNewPartner(ABaseEnemy* Enemy);
	void RemoveFromSquad(ABaseEnemy* EnemyToRemove);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	int32 SquadValue = 5;

	UPROPERTY(VisibleAnywhere, Category = "Squad")
	TArray<ABaseEnemy*> SquadMembers;
	
	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	TArray<TSubclassOf<ABaseEnemy>> EnemyTypes;

	UPROPERTY(VisibleAnywhere)
	ASquadManager* MySquadManager;

	void CreateSquadMembers();
	void BindAllSquadMembers();
	void BindPartners(ABaseEnemy* EnemyOne, ABaseEnemy* EnemyTwo);

};
