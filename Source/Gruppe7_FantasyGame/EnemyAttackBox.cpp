// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "EnemyAttackBox.h"


// Sets default values
AEnemyAttackBox::AEnemyAttackBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision object and RootObject
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = RootBox;
	RootBox->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void AEnemyAttackBox::BeginPlay()
{
	Super::BeginPlay();

	// DEBUG.
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("ENEMY - PHYSICAL ATTACK!"));
}

// Called every frame
void AEnemyAttackBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
	}
}