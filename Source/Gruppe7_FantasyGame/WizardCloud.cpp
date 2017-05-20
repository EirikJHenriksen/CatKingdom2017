// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "WizardCloud.h"
#include "FantasyGameInstance.h"


// Sets default values
AWizardCloud::AWizardCloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision object and RootObject
	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;
}

// Called when the game starts or when spawned
void AWizardCloud::BeginPlay()
{
	Super::BeginPlay();
	
	cloudIsActive = false;
}

// Called every frame
void AWizardCloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetMana() <= 0.5f && !cloudIsActive)
	{	
		cloudIsActive = true;

		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Player needs mana!"));

		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWizardCloud::Spawn, FMath::RandRange(RandomMin, RandomMax), false);
	}
}

void AWizardCloud::Spawn()
{	
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("MANA IS SPAWNED!"));

	//Doesn't actually spawn it, just moves it.
	SetActorLocation(FVector(SpawnX, SpawnY, SpawnZ));
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	cloudIsActive = false;
}

