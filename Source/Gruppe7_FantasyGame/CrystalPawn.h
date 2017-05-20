// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CrystalPawn.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API ACrystalPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACrystalPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere;


	// Makes the potion spin. And float.
	int Rotator = 1;
	float TimeCounter = 0.f;

	float DistanceToPlayer();

	void FloatUpDown();

private:

	float HomeZ;

};
