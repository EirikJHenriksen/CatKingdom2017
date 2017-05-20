// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Enemy_AI_Controller.generated.h"


 // An enum class for which state the enemy is in
UENUM(BlueprintType) //"BlueprintType" is essential to include
enum class StateEnum : uint8
{
	IDLE,
	FOLLOW,
	RETURN,
	ATTACK
};


UCLASS()
class GRUPPE7_FANTASYGAME_API AEnemy_AI_Controller : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Enum)
	StateEnum State;
	
public:
	AEnemy_AI_Controller();

	virtual void Possess(APawn *InPawn) override;


	virtual void Tick(float DeltaTime) override;

	//FVector MyHome;

	void IdleState();
	void ApproachState();
	void ReturnState();
	//void AttackState();

private:

};
