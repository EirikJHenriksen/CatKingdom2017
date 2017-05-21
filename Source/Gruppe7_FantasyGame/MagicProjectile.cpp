// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "Gruppe7_FantasyGameCharacter.h"
#include "MagicProjectile.h"
#include "BossSpellFire.h"


// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("MProjectile"));

	CollisionComponent->OnComponentHit.AddDynamic(this, &AMagicProjectile::OnHit);

	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f; //Sett til 1000.f hvis spiller akselerasjon ikke fungerer.
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->Bounciness = 1.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	// Attenuation
	WaterImpactAtt = CreateDefaultSubobject<USoundAttenuation>(TEXT("WaterImpactlAttenuation"));
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMagicProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeLived += DeltaTime;
	if (TimeLived > TimeBeforeDestroy)
	{
		this->Destroy();
	}
}

void AMagicProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{	
	if (OtherActor->IsA(ABossSpellFire::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Purple, TEXT("IMPACT!"));
		OtherActor->Destroy();
	}

	Destroy();
}

// Function that initializes the projectile's velocity in the shoot direction.
void AMagicProjectile::FireInDirection(const FVector& ShootDirection)
{	
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AMagicProjectile::Destroy()
{
	Super::Destroy();


	//Spiller av SFX.
	float RandomValue = FMath::RandRange(0.8f, 1.2f);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WaterImpactSound, GetActorLocation(), 0.5f, RandomValue, 0.f, WaterImpactAtt);

	//Spiller av VFX.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactMagicFX, GetTransform(), true);
}