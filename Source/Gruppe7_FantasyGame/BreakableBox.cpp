// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "MagicProjectile.h"
#include "PhysAttackBox.h"
//DEBUG.
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
//DEBUG.
#include "BreakableBox.h"


// Sets default values
ABreakableBox::ABreakableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision object and RootObject
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ABreakableBox::OnOverlap);
}

// Called when the game starts or when spawned
void ABreakableBox::BeginPlay()
{
	Super::BeginPlay();
	Health = 1.f;
}

// Called every frame
void ABreakableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakableBox::RecieveDamage(float Damage)
{
	Health -= Damage;

	if (Health < 0.f)
	{
		// Insert code that can spawn random things here!!!
		//RandomNumber = FMath::FRandRange(0.f, 10.f);

		// DEBUG.
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DESTRUCTION!"));
		
		Destroy();
	}
}

void ABreakableBox::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{	
	//Registrerer ikke kollisjoner... Må finne ut av dette.

	// DEBUG.
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OVERLAP!"));

	if (OtherActor->IsA(AMagicProjectile::StaticClass()))
	{	
		OtherActor->Destroy();
		ABreakableBox::RecieveDamage(0.5f);
		
		// DEBUG.
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Magic damage!"));
	}

	if (OtherActor->IsA(APhysAttackBox::StaticClass()))
	{	
		OtherActor->Destroy();
		ABreakableBox::RecieveDamage(0.25f);
		
		// DEBUG.
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Physical damage!"));
	}
}