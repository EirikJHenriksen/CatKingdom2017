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
	// to display the cost of the next "crystal door"
	// starts as 1 because that's the cost of the first door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crystal)
	int NextCost = 1;

	// Sets default values for main character.

	UFantasyGameInstance(const FObjectInitializer& ObjectInitializer);

	//////////////////////////////////////////////////////////////////
	// Player variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
		float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
		int SpellSelect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
		int CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameVariables)
		bool PlayerIsDead;

	////////////////////////////////////////////////////////////////////
	// Game variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameVariables)
		bool BossFightActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameVariables)
		bool GameIsWon;

	// Used to stop GameMode from creating a menu on every BeginPlay. It's only supposed to do it as a start menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
		bool IsFirstTimeMenuCalled = true;

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

	//void SetPlayerVelocity(FVector Velocity);

	//FVector GetPlayerVelocity();
};