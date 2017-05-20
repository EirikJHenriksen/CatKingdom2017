// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ConeOfFire.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API AConeOfFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConeOfFire();

	// Sets up collision.
	UPROPERTY(EditAnywhere)
		USphereComponent* CollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 1.f;

		float TimeLived{ 0 };

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;
};
