// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FinalBoss.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API AFinalBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFinalBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/////////////////////////////////////////
	// Stats.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Health;

	/////////////////////////////////////////
	// SPAWNING.
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABossSpellFire> SpellFireBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABossSpellWater> SpellWaterBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABossSpellNature> SpellNatureBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemyBaseClass> FireEnemyBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemyBaseClass> WaterEnemyBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemyBaseClass> NatureEnemyBlueprint;

	/////////////////////////////////////////
	// SUMMON LOCATION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Summon SPAWN")
		float SpawnX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Summon SPAWN")
		float SpawnY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Summon SPAWN")
		float SpawnZ = 0;

	/////////////////////////////////////////
	// LOCATION VARIABLES
	void UpdateDirection();

	FVector CurrentPlayerLocation;

	FVector LookVector;

	int Element = 0;

	/////////////////////////////////////////
	// Animation hooks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool IsDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool IsDead;

	/////////////////////////////////////////
	// TELEPORTATION VARIABLES.
	void Teleport();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool fightInProgress;
	
	bool canTeleport;
	
	bool firstTeleport;
	
	bool canBeHurt;

	FTimerHandle TeleportTimerHandle;

	FTimerHandle FirstTeleportTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport timers")
		float RandomMin = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport timers")
		float RandomMax = 10.f;

	float RandomTeleportTime = 0.f;

	// Teleport locations.
	
	// FIRE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport FIRE")
		float FireX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport FIRE")
		float FireY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport FIRE")
		float FireZ = 0;

	// WATER
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport WATER")
		float WaterX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport WATER")
		float WaterY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport WATER")
		float WaterZ = 0;

	// NATURE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport NATURE")
		float NatureX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport NATURE")
		float NatureY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport NATURE")
		float NatureZ = 0;

	//////////////////////////////////////
	// Action functions.
	void Attack();

	void SummonEnemy();

	bool isAttacking;

	FTimerHandle AttackTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack timers")
		float AttackRandomMin = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack timers")
		float AttackRandomMax = 8.f;

	float RandomAttackTime = 0.f;


	// Overlap function
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	void DeathCheck();

};
