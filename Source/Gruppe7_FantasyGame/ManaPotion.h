// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ManaPotion.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API AManaPotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AManaPotion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere;	

	// Makes the potion spin.
	int Rotator = 1;
};
