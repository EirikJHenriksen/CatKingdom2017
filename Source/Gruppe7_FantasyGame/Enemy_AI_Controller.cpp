// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "EnemyBaseClass.h"
#include "Enemy_AI_Controller.h"


AEnemy_AI_Controller::AEnemy_AI_Controller()
{
	// all enemies start out in idle state
	State = StateEnum::IDLE;
}

// Called every frame
void AEnemy_AI_Controller::Tick(float DeltaTime)
{
Super::Tick(DeltaTime);

// check if the character is dead
if (Cast<AEnemyBaseClass>(GetCharacter())->IsDead)
{
	State = StateEnum::DEAD;
}

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
case StateEnum::DEAD:
	DeadState();
	break;
default:
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Switch not working in AIController"));
}
}

// FUNCTIONS FOR STATES START HERE

///// IDLE /////
void AEnemy_AI_Controller::IdleState()
{
	Cast<AEnemyBaseClass>(GetCharacter())->IsAttacking = false;
	///// check for change /////
	if (Cast<AEnemyBaseClass>(GetCharacter())->CanSeePlayer())
	{
		State = StateEnum::FOLLOW;
	}
	// Will run after you if you hurt them:
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

	// stop attack animation if too far away
	if ( Cast<AEnemyBaseClass>(GetCharacter())->GetDistanceToPlayer() > 100.f )
	{
		Cast<AEnemyBaseClass>(GetCharacter())->IsAttacking = false;
	}
	
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
	Cast<AEnemyBaseClass>(GetCharacter())->IsAttacking = false;
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

void AEnemy_AI_Controller::DeadState()
{
	Cast<AEnemyBaseClass>(GetCharacter())->IsAttacking = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("DEAD"));
	StopMovement();
	// nothing to do here, this is the final stop :'(
}

StateEnum AEnemy_AI_Controller::EnumGetter()
{
	return State;
}