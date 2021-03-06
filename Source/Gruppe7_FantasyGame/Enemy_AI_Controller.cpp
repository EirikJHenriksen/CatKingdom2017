// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "EnemyBaseClass.h"
#include "FantasyGameInstance.h"
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

	// check if the player is dead, in which case celebrate by standing idle
	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerIsDead())
	{
		Cast<AEnemyBaseClass>(GetCharacter())->AIState = 1;
		IdleState();
	}
	else 
	{
		// Each tick run the function fitting current state
		switch (State)
		{
		case StateEnum::IDLE:
			Cast<AEnemyBaseClass>(GetCharacter())->AIState = 1;
			IdleState();
			break;
		case StateEnum::FOLLOW:
			Cast<AEnemyBaseClass>(GetCharacter())->AIState = 2;
			ApproachState();
			break;
		case StateEnum::RETURN:
			Cast<AEnemyBaseClass>(GetCharacter())->AIState = 2;
			ReturnState();
			break;
		case StateEnum::DEAD:
			Cast<AEnemyBaseClass>(GetCharacter())->AIState = 4;
			DeadState();
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Switch not working in AIController"));
		}
	}
}

// FUNCTIONS FOR STATES START HERE

///// IDLE /////
void AEnemy_AI_Controller::IdleState()
{	
	Cast<AEnemyBaseClass>(GetCharacter())->GetCharacterMovement()->MaxWalkSpeed = 300.f;

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

	// Roaming stuff!!!
	if (Cast<AEnemyBaseClass>(GetCharacter())->GetRoaming())
	{	
		//G�r til destinasjon!!!
		MoveToLocation(Cast<AEnemyBaseClass>(GetCharacter())->GetMyDestination(), 5.f, true, true, true, false, 0, true);
	}
	else
	{
		//Returnerer til startpunkt!!!
		State = StateEnum::RETURN;
	}
}

///// FOLLOW /////
void AEnemy_AI_Controller::ApproachState()
{	
	if (!Cast<AEnemyBaseClass>(GetCharacter())->SlowdownActive)
	{
		Cast<AEnemyBaseClass>(GetCharacter())->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}

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
	Cast<AEnemyBaseClass>(GetCharacter())->GetCharacterMovement()->MaxWalkSpeed = 300.f;

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
	StopMovement();
	// nothing to do here, this is the final stop :'(
}