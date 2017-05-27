// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "Gruppe7_FantasyGameCharacter.h"
#include "FantasyGameInstance.h"

// Sets default values
UFantasyGameInstance::UFantasyGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Health = 1.f;
	Mana = 1.f;

	CurrentLevel = 1;

	GameIsWon = false;

	BossFightActive = false;

	BossIsDead = false;
}

float UFantasyGameInstance::GetHealth()
{
	return Health;
}

float UFantasyGameInstance::GetMana()
{
	return Mana;
}

void UFantasyGameInstance::SetHealth(float Input)
{
	Health = Input;
}

void UFantasyGameInstance::SetMana(float Input)
{
	Mana = Input;
}

void UFantasyGameInstance::DrainHealth(float Input)
{
	Health -= Input;
}

void UFantasyGameInstance::DrainMana(float Input)
{
	Mana -= Input;
}

void UFantasyGameInstance::RestoreHealth(float Input)
{
	Health += Input;
	// Sørger for at Health ikke går over 100%.
	if (Health > 1.f)
	{
		Health = 1.f;
	}
}

void UFantasyGameInstance::RestoreMana(float Input)
{
	Mana += Input;
	// Sørger for at Mana ikke går over 100%.
	if (Mana > 1.f)
	{
		Mana = 1.f;
	}
}

void UFantasyGameInstance::SwapUp()
{
	++SpellSelect;

	if (SpellSelect == 4)
	{
		SpellSelect = 0;
	}
}

void UFantasyGameInstance::SwapDown()
{
	--SpellSelect;

	if (SpellSelect == -1)
	{
		SpellSelect = 3;
	}
}

int UFantasyGameInstance::GetCurrentSpell()
{
	return SpellSelect;
}

void UFantasyGameInstance::SetPlayerLocation(FVector Location)
{
	PlayerLocation = Location;
}

FVector UFantasyGameInstance::GetPlayerLocation()
{
	return PlayerLocation;
}

void UFantasyGameInstance::SelectWater()
{
	SpellSelect = 0;
}

void UFantasyGameInstance::SelectFire()
{
	SpellSelect = 1;
}

void UFantasyGameInstance::SelectThorns()
{
	SpellSelect = 2;
}

void UFantasyGameInstance::SelectHealing()
{
	SpellSelect = 3;
}

void UFantasyGameInstance::SetCurrentLevel(int level)
{
	CurrentLevel = level;
}

int UFantasyGameInstance::GetCurrentLevel()
{
	return CurrentLevel;
}

void UFantasyGameInstance::SetBossFightActive(bool status)
{
	BossFightActive = status;
}

bool UFantasyGameInstance::GetBossFightActive()
{
	return BossFightActive;
}

void UFantasyGameInstance::SetGameIsWon(bool victory)
{
	GameIsWon = victory;
}

bool UFantasyGameInstance::GetGameIsWon()
{
	return GameIsWon;
}

void UFantasyGameInstance::SetPlayerIsDead(bool dead)
{
	PlayerIsDead = dead;
}

bool UFantasyGameInstance::GetPlayerIsDead()
{
	return PlayerIsDead;
}

void UFantasyGameInstance::SetBossIsDead(bool status)
{
	BossIsDead = status;
}

bool UFantasyGameInstance::GetBossIsDead()
{
	return BossIsDead;
}

//void UFantasyGameInstance::SetPlayerVelocity(FVector Velocity)
//{
//	PlayerVelocity = Velocity;
//}
//
//FVector UFantasyGameInstance::GetPlayerVelocity()
//{
//	return PlayerVelocity;
//}