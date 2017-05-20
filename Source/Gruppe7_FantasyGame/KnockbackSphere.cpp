// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "KnockbackSphere.h"


// Sets default values
AKnockbackSphere::AKnockbackSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("MProjectile"));
}

// Called when the game starts or when spawned
void AKnockbackSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnockbackSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Makes the fire grow over time. Starts small and ends up big.
	float CurrentScale = CollisionComponent->GetComponentScale().X;
	CurrentScale += DeltaTime * 5.f;
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	CollisionComponent->SetWorldScale3D(FVector(CurrentScale));

	// Lag en release funksjon som gjør at flammen eksisterer så lenge knappen holdes inne.

	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
	}
}

