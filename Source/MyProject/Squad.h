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

	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	int32 NumberOfExplosive;

	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	int32 NumberOfMelee;

	UPROPERTY(VisibleAnywhere, Category = "Squad")
	TArray<ABaseEnemy*> SquadMembers;
	
	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	TArray<TSubclassOf<ABaseEnemy>> EnemyTypes;

	UPROPERTY(VisibleAnywhere, Category = "Squad")
	ASquadManager* MySquadManager;

	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	bool RandomlyGenerated;

	UPROPERTY(EditDefaultsOnly, Category = "Squad")
	bool PartnerEnabled;

	UPROPERTY(VisibleAnywhere)
	ABaseEnemy* MemberWithoutPartner;

	void CreateRandomSquadMembers();
	void CreateSpecifiedSquadMembers();
	void BindAllSquadMembers();
	void BindPartners(ABaseEnemy* EnemyOne, ABaseEnemy* EnemyTwo);

};
