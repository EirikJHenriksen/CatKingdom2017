// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "BossSpellFire.h"
#include "FantasyGameInstance.h"
#include "MagicProjectile.h"
#include "ConeOfFire.h"
#include "CircleOfThorns.h"


// Sets default values
ABossSpellFire::ABossSpellFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

	CollisionComponent->OnComponentHit.AddDynamic(this, &ABossSpellFire::OnHit);

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	ProjectileMovementComponent->OnProjectileStop.AddDynamic(this, &ABossSpellFire::OnStop);
}

// Called when the game starts or when spawned
void ABossSpellFire::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABossSpellFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keeps track of the players location.
	CurrentPlayerLocation = Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerLocation();

	SetActorRotation(TargetVector.Rotation() + FRotator(180.f, 0.f, 0.f));

	UpdateTarget();

	ProjectileMovementComponent->OnProjectileStop;

	if (Cast<UFantasyGameInstance>(GetGameInstance())->PlayerIsDead)
	{
		Destroy();
	}
}

void ABossSpellFire::UpdateTarget()
{
	TargetVector = GetActorLocation() - CurrentPlayerLocation;

	VelocityVector = GetActorForwardVector() * 1000.f;

	ProjectileMovementComponent->Velocity = VelocityVector;
}

void ABossSpellFire::OnStop(const FHitResult& HitResult)
{
	Destroy();
}

void ABossSpellFire::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(ACircleOfThorns::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Purple, TEXT("IMPACT!"));
		Destroy();
	}
}

void ABossSpellFire::Destroy()
{
	Super::Destroy();

	//Spiller av VFX.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactMagicFX, GetTransform(), true);
}