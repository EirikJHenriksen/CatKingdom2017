// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "ImpactSoundWater.h"


// Sets default values
AImpactSoundWater::AImpactSoundWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Controlls water spell impact audio settings
	SplashSound = CreateDefaultSubobject<UAudioComponent>(TEXT("WaterImpactSound"));
	SplashSound->PitchModulationMin = 0.8f;
	SplashSound->PitchModulationMax = 1.2f;
}

// Called when the game starts or when spawned
void AImpactSoundWater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AImpactSoundWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

