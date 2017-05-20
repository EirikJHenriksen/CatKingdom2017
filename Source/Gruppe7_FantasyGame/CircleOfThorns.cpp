// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "CircleOfThorns.h"
#include "BossSpellFire.h"


// Sets default values
ACircleOfThorns::ACircleOfThorns()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision object and RootObject
	RootCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootCollision;
	RootCollision->bGenerateOverlapEvents = true;
	RootCollision->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
	//RootCollision->;

	RootCollision->OnComponentHit.AddDynamic(this, &ACircleOfThorns::OnHit);
}

// Called when the game starts or when spawned
void ACircleOfThorns::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, -50.f));
}

// Called every frame
void ACircleOfThorns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Makes it grow up from the ground.
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);
	if (!Stopped)
	{
		CurrentVelocity.Z = 800.0f;
	}
	if (NewLocation.Z > 180.0f)
	{
		Stopped = true;
		CurrentVelocity.Z = 0.0f;
	}

	TimeLived += DeltaTime;
	if (TimeLived >= TimeBeforeRetracting)
	{	
		CurrentVelocity.Z = -400.0f;
	}

	if (TimeLived >= TimeBeforeDestroy)
	{
		Destroy();
	}
}

void ACircleOfThorns::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(ABossSpellFire::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Purple, TEXT("IMPACT!"));
		OtherActor->Destroy();
	}
}