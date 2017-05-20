// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "CircleOfFire.h"


// Sets default values
ACircleOfFire::ACircleOfFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision object and RootObject
	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;
	RootSphere->bGenerateOverlapEvents = true;
	RootSphere->SetWorldScale3D(FVector(10.f, 10.f, 10.f));
}

// Called when the game starts or when spawned
void ACircleOfFire::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACircleOfFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Makes it grow up from the ground.
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);
	if (!Stopped)
	{
		CurrentVelocity.Z = 100.0f;
	}
	if (NewLocation.Z > 80.0f)
	{	
		Stopped = true;
		CurrentVelocity.Z = 0.0f;
	}

	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
	}
}