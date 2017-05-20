// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PhysAttackBox.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API APhysAttackBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysAttackBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox;
	
	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 0.1f;

		float TimeLived{ 0 };
};
