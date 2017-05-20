// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "CrystalPawn.h"
#include "CrystalAIController.h"


//void ACrystalAIController::Possess(APawn *InPawn)
//{
//	Super::Possess(InPawn);
//	ACrystalPawn *Char = Cast<ACrystalPawn>(InPawn);
//}

void ACrystalAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// this works: GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Crystal AI controller"));

	MoveToLocation(FVector(0,0,0), 5.f, true, true, true, true, 0, true);
	// MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 5.f, true, true, true, 0, true);
}