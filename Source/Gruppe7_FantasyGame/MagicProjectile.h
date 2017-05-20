// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MagicProjectile.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API AMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// What happens when destroyed.
	void Destroy();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Sets up collision.
	UPROPERTY(EditAnywhere)
		USphereComponent* CollisionComponent;

	//UPROPERTY(EditAnywhere)
		//USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere)
		float TimeBeforeDestroy = 10.f;

		float TimeLived{ 0 };

	// VFX.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXs")
		UParticleSystem *ImpactMagicFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXs")
		UParticleSystem *MagiSpark;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);
};
