// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "Gruppe7_FantasyGameCharacter.h"
#include "FantasyGameInstance.h"
#include "CrystalPawn.h"


// Sets default values
ACrystalPawn::ACrystalPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;
}

// Called when the game starts or when spawned
void ACrystalPawn::BeginPlay()
{
	Super::BeginPlay();
	FVector HomeLocation = GetActorLocation();
	HomeZ = HomeLocation.Z;
}

// Called every frame
void ACrystalPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	++Rotator;
	++TimeCounter;
	SetActorRotation(FRotator(0.f, (1.f * Rotator), 0.f));

	if (Rotator >= 360)
	{
		Rotator = 0;
	}

	// bob up and down here?
	FloatUpDown();
}

// follow player when close
// gets the distance to player
float ACrystalPawn::DistanceToPlayer()
{
	FVector CurrentPlayerLocation = Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerLocation();
	FVector DistanceVector = GetActorLocation() - CurrentPlayerLocation;
	return DistanceVector.Size();
}

void ACrystalPawn::FloatUpDown()
{
	//auto World = GetWorld();
	FVector MyActorLocation = GetActorLocation();
	// This controls the manner of the bobbing. MATHMATHICAL!
	MyActorLocation.Z = HomeZ + (FMath::Sin(TimeCounter / 50) * 30);
	SetActorLocation(MyActorLocation, false);
}