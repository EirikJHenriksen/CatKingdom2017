// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyBaseClass.generated.h"

// An enum class that hold the kinds of elements enemies can belong to 
UENUM(BlueprintType) //"BlueprintType" is essential to include
enum class ElementsEnum : uint8
{
	FIRE,
	WATER,
	NATURE 
};

UCLASS()
class GRUPPE7_FANTASYGAME_API AEnemyBaseClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseClass();

	// Selects physical hitbox.
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AEnemyAttackBox> EnemyAttackBlueprint;

	// Mana
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AManaPotion> ManaBlueprint;

	// Mana
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AHealthPotion> HealthBlueprint;

	// CollectionPickup
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACrystalPawn> CrystalBlueprint;

	///////////////////////////////////////////
	// Roaming values.
	UPROPERTY(EditAnywhere, Category = "NPC - Roaming - WALKING")
		float WalkRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "NPC - Roaming - WAITING")
		float WantsToGoMin = 0.f; 

	UPROPERTY(EditAnywhere, Category = "NPC - Roaming - WAITING")
		float WantsToGoMax = 0.f;

	UPROPERTY(EditAnywhere, Category = "NPC - Roaming - WALKING")
		float RoamingMin = 0.f;

	UPROPERTY(EditAnywhere, Category = "NPC - Roaming - WALKING")
		float RoamingMax = 0.f;

	///////////////////////////////////////////
	// SFX STUFF

	// Sounds
	UPROPERTY(EditAnywhere)
		USoundBase* WaterImpactSound;

	// Sounds
	UPROPERTY(EditAnywhere)
		USoundBase* PhysImpactSound;

	/////////////////////////////////////
	// VFX.

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystem *HitFX;

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystem *WaterHitFX;

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystem* DeathPoof;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MeleeAttack();

	// getters
	float GetDistanceToPlayer();

	FVector GetMyStartLocation();

	bool GetInPain();

	// sets DistanceToPlayer
	void UpdateDistance();

	// Random walk functions and variables.
	void WalkRandomly();

	void WalkRandomlyEnd();

	FVector GetMyDestination();

	bool GetRoaming();

	bool WantsToGo;

	bool Roaming;

	FTimerHandle WantsToGoTimerHandle;

	FTimerHandle RoamingEndTimerHandle;

	bool SlowdownActive;

	UPROPERTY(EditAnywhere)
		UNavigationSystem* EnemyNavSys;

	// Overlap function.
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void DeathCheck();

	void Death();

	void EnemyIsHit(float force, float duration);

	void SlowdownOver();

	// Distance detection variables.
	FVector CurrentPlayerLocation;
	FVector DistanceVector;
	float DistanceFloat;

	// Elements for enemie
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		ElementsEnum Element;

	bool CanSeePlayer();

	// enemies follow you if they are hurt, this is a countdown until they will not follow
	void PainForgetter();

	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	bool IsDead = false;

	UPROPERTY (BlueprintReadWrite, Category = "Animation")
	bool IsAttacking = false;

	// for animation
	UPROPERTY(BlueprintReadWrite, Category = "State")
		int32 AIState = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/////////////////
	// Timers for attack.
	float AttackTimer = 30.f;

	/* Handle for slowdown timer */
	FTimerHandle SlowdownTimerHandle;

private:
	// enemies HP
	UPROPERTY(EditAnywhere)
		float HealthPoints = 100.f;

	// saves where player starts, used to go back "home"
	UPROPERTY(EditAnywhere)
		FVector MyStartLocation;

	// A random place to walk to.
	FVector RandomDestination;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 600.f;

	// holds the distance between enemy and player
	float DistanceToPlayer = 1000.f; // just initializing a arbitrary value

	// How much different attacks hurt
	float DamageMelee = 20.f;
	// these are used depending on the enemies element type and the magic attacks element type
	float DamageMyWeakness = 60.f;
	float DamageMyEqual = 25.f;
	float DamageLeastEffective = 10.f;

	// SFX.
	UPROPERTY(EditAnywhere, Category = "SFX")
		USoundBase* AttackSound;
	UPROPERTY(EditAnywhere, Category = "SFX")
		USoundBase* EnemyDeathSound;
	UPROPERTY(EditAnywhere, Category = "SFX")
		USoundBase* EnemyHurtSound;

	//enemies follow you if they are hurt, while this is more then 0
	float RememberPain = 0;

	UPROPERTY(EditAnywhere, Category = "SFX")
	int AttackSoundDelayLength = 90;

	int AttackSoundDelay = 0;
};
