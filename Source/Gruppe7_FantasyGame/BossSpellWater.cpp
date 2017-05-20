// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "BossSpellWater.h"
#include "FantasyGameInstance.h"
#include "CircleOfThorns.h"


// Sets default values
ABossSpellWater::ABossSpellWater()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	//CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("MProjectile"));
	CollisionComponent->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

	CollisionComponent->OnComponentHit.AddDynamic(this, &ABossSpellWater::OnHit);

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	//ProjectileMovementComponent->Bounciness = 1.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	//ProjectileMovementComponent->bIsHomingProjectile = true;

	ProjectileMovementComponent->OnProjectileStop.AddDynamic(this, &ABossSpellWater::OnStop);
}

// Called when the game starts or when spawned
void ABossSpellWater::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABossSpellWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keeps track of the players location. IMPORTANT THAT IT STAYS IN TICK FUNCTION.
	CurrentPlayerLocation = Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerLocation();

	SetActorRotation(TargetVector.Rotation() + FRotator(180.f, 0.f, 0.f));

	UpdateTarget();

	ProjectileMovementComponent->OnProjectileStop;
}

void ABossSpellWater::UpdateTarget()
{
	TargetVector = GetActorLocation() - CurrentPlayerLocation;

	VelocityVector = GetActorForwardVector() * 1000.f;

	ProjectileMovementComponent->Velocity = VelocityVector;
}

void ABossSpellWater::OnStop(const FHitResult& HitResult)
{
	//Destroy();
}

void ABossSpellWater::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//Destroy();
}

void ABossSpellWater::Destroy()
{
	Super::Destroy();

	//Spiller av VFX.
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactMagicFX, GetTransform(), true);
	//Lyd effekter?
}