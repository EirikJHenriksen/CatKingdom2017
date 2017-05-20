// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyBaseClass.h"
#include "Enemy_AI_Controller.h"


AEnemy_AI_Controller::AEnemy_AI_Controller()
{
	// all enemies start out in idle state
	State = StateEnum::IDLE;
}

void AEnemy_AI_Controller::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);
	AEnemyBaseClass *Char = Cast<AEnemyBaseClass>(InPawn);
}
//
// Called every frame
void AEnemy_AI_Controller::Tick(float DeltaTime)
{
Super::Tick(DeltaTime);

// Each tick run the function fitting current state
switch (State)
{
case StateEnum::IDLE:
	// weak
	IdleState();
	break;
case StateEnum::FOLLOW:
	ApproachState();
	break;
case StateEnum::RETURN:
	ReturnState();
	break;
//case StateEnum::ATTACK:
//	AttackState();
//	break;
default:
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Switch not working in AIController"));
}
}

// FUNCTIONS FOR STATES START HERE

///// IDLE /////
void AEnemy_AI_Controller::IdleState()
{

	///// check for change /////
	if (Cast<AEnemyBaseClass>(GetCharacter())->CanSeePlayer())
	{
		State = StateEnum::FOLLOW;
	}
	if (Cast<AEnemyBaseClass>(GetCharacter())->GetInPain())
	{
		State = StateEnum::FOLLOW;
	}
}

///// FOLLOW /////
void AEnemy_AI_Controller::ApproachState()
{
	// runs to the player
	MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 5.f, true, true, true, 0, true);
	
	///// check for change /////
	if (!Cast<AEnemyBaseClass>(GetCharacter())->CanSeePlayer())
	{
		State = StateEnum::RETURN;
	}
	if (Cast<AEnemyBaseClass>(GetCharacter())->GetInPain())
	{
		State = StateEnum::FOLLOW;
	}
}

///// RETURN /////
void AEnemy_AI_Controller::ReturnState()
{
	// go home
	FVector MyHome = Cast<AEnemyBaseClass>(GetCharacter())->GetMyStartLocation();
	FVector CurrentLocation = GetCharacter()->GetActorLocation();
	FVector DistanceFromHomeVector = CurrentLocation - MyHome;
	float DistanceFromHome = DistanceFromHomeVector.Size();
	MoveToLocation(MyHome, 5.f, true, true, true, true, 0, true);

	///// check for change /////
	if (DistanceFromHomeVector.Size() < 50)
	{
		State = StateEnum::IDLE;
	}
	else if (Cast<AEnemyBaseClass>(GetCharacter())->CanSeePlayer())
	{
		State = StateEnum::FOLLOW;
	}
	if (Cast<AEnemyBaseClass>(GetCharacter())->GetInPain())
	{
		State = StateEnum::FOLLOW;
	}
}