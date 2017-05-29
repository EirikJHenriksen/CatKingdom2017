// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "FantasyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GRUPPE7_FANTASYGAME_API UFantasyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Sets default values for main character.

	UFantasyGameInstance(const FObjectInitializer& ObjectInitializer);

	//////////////////////////////////////////////////////////////////
	// Player variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
		float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
		int SpellSelect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
		int CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Variables")
		bool PlayerIsDead;

	////////////////////////////////////////////////////////////////////
	// Game variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Variables")
		bool BossFightActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Variables")
		bool GameIsWon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Variables")
		bool BossAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Variables")
		bool BossIsDead;

	// to display the cost of the next "crystal door"
	// starts as 1 because that's the cost of the first door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Variables")
		int NextCost = 1;

	// Used to stop GameMode from creating a menu on every BeginPlay. It's only supposed to do it as a start menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Variables")
		bool IsFirstTimeMenuCalled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Variables")
		bool MainMenuIsNotActive = false;

	FVector PlayerLocation;

	FVector PlayerVelocity;

	float GetHealth();

	float GetMana();

	void SetHealth(float Input);

	void SetMana(float Input);

	void DrainHealth(float Input);

	void DrainMana(float Input);

	void RestoreHealth(float Input);
	
	void RestoreMana(float Input);

	void SwapUp();

	void SwapDown();

	int GetCurrentSpell();
	
	void SetPlayerLocation(FVector Location);
	
	FVector GetPlayerLocation();

	void SelectWater();

	void SelectFire();

	void SelectThorns();

	void SelectHealing();

	void SetCurrentLevel(int level);

	int GetCurrentLevel();

	void SetBossFightActive(bool status);

	bool GetBossFightActive();

	void SetGameIsWon(bool victory);

	bool GetGameIsWon();

	void SetPlayerIsDead(bool dead);

	bool GetPlayerIsDead();

	void SetBossIsDead(bool status);

	bool GetBossIsDead();

	void SetBossAttack(bool status);

	bool GetBossAttack();

	void SetNextCost(int cost);
};