// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CircleOfThorns.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API ACircleOfThorns : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACircleOfThorns();

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootCollision;

	// TEST.
	FVector CurrentVelocity;

	bool Stopped = false;

	// VFX.
	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystem* EarthEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	UPROPERTY(EditAnywhere)
		float TimeBeforeRetracting = 4.f;

	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 6.f;

	float TimeLived{ 0 };
};