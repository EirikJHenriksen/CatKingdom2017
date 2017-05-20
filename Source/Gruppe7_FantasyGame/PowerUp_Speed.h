// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PowerUp_Speed.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API APowerUp_Speed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp_Speed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere;

	// Makes the powerup spin.
	int Rotator = 1;
};
