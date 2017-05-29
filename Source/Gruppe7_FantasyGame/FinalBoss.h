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
	// VOICE.
	UPROPERTY(EditAnywhere)
		USoundBase* BossIntro;

	UPROPERTY(EditAnywhere)
		USoundBase* BossHurt;

	UPROPERTY(EditAnywhere)
		USoundBase* BossLaugh;

	UPROPERTY(EditAnywhere)
		USoundBase* BossAnnoyed;

	UPROPERTY(EditAnywhere)
		USoundBase* BossDefeatComplain;

	UPROPERTY(EditAnywhere)
		USoundBase* BossDeathScream;

	UPROPERTY(EditAnywhere)
		USoundBase* BossWin;

	void VoiceIsFinished();

	bool VoiceIsActive;

	bool BossIsAnnoyed;

	bool BossWinVoicePlayed;

	FTimerHandle VoiceIsActiveTimerHandle;

	/////////////////////////////////////////
	// SFX.
	UPROPERTY(EditAnywhere)
		USoundBase* MagicAttackSound;

	UPROPERTY(EditAnywhere)
		USoundBase* TeleportSound;

	UPROPERTY(EditAnywhere)
		USoundBase* FailSparkSound;

	/////////////////////////////////////////
	// VFX.

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystem *WaterHitFX;

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystem *HitFailFX;

	/////////////////////////////////////////
	// Stats.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Health;

	/////////////////////////////////////////
	// SPAWNING.
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ABossSpellFire> SpellFireBlueprint;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool animIsTeleporting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool animStoppedTeleporting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool animIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool animStoppedAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool animIsSummoning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool animStoppedSummoning;
		
	FTimerHandle AnimDyingTimerHandle;

	FTimerHandle AnimAttackTimerHandle;

	FTimerHandle AnimTeleportTimerHandle;

	FTimerHandle AnimSummonTimerHandle;

	/////////////////////////////////////////
	// TELEPORTATION VARIABLES.
	void TeleportFirstStage();

	void TeleportSecondStage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Fight")
		bool fightInProgress;
	
	bool firstTeleport;

	bool firstTeleportOver;
	
	bool canBeHurt;

	FTimerHandle TeleportTimerHandle;

	FTimerHandle FirstTeleportTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action timers")
		float RandomMin = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action timers")
		float RandomMax = 6.f;

	float RandomActionTime = 0.f;

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
	void DoSomething();

	void AttackFirstStage();

	void AttackSecondStage();

	void SummonFirstStage();

	void SummonSecondStage();

	int TheActionInt = 0;

	bool isAttacking;

	bool isDoingSomething;

	bool PlayerIsDead;

	FTimerHandle AttackTimerHandle;

	FTimerHandle SummonTimerHandle;

	FTimerHandle BossDeadTimerHandle;

	// Overlap function
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void ResistAttack();

	void IsNowDead();
	
	void DeathCheck();

	void GameWon();

};
