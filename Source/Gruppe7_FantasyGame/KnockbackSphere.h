// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KnockbackSphere.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API AKnockbackSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKnockbackSphere();

	// Sets up collision.
	UPROPERTY(EditAnywhere)
		USphereComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 0.5f;

		float TimeLived{ 0 };
	
};
