// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "EnemyBaseClass.h"
#include "MagicProjectile.h"
#include "ConeOfFire.h"
#include "CircleOfThorns.h"
#include "PhysAttackBox.h"
#include "KnockbackSphere.h"
#include "Gruppe7_FantasyGameCharacter.h"
#include "FantasyGameInstance.h"
#include "ManaPotion.h"
#include "HealthPotion.h"
#include "CrystalPawn.h"
#include "EnemyAttackBox.h"

// Sets default values
AEnemyBaseClass::AEnemyBaseClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBaseClass::OnOverlap);

	// Sets control parameters
	GetCharacterMovement()->AirControl = 0.f;
	GetCharacterMovement()->AirControlBoostMultiplier = 0.f;
	GetCharacterMovement()->AirControlBoostVelocityThreshold = 0.f;

	// Attenuation
	DamageAtt = CreateDefaultSubobject<USoundAttenuation>(TEXT("WaterImpactlAttenuation"));
}

// Called when the game starts or when spawned
void AEnemyBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
	MyStartLocation = GetActorLocation();

	// set movement speed
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

// Called every frame
void AEnemyBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keeps track of the players location. IMPORTANT THAT IT STAYS IN TICK FUNCTION.
	CurrentPlayerLocation = Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerLocation();

	if (RememberPain != 0)
	{
		PainForgetter();
	}
}

// getters
float AEnemyBaseClass::GetDistanceToPlayer() { return DistanceToPlayer; }
FVector AEnemyBaseClass::GetMyStartLocation() { return MyStartLocation; }

bool AEnemyBaseClass::GetInPain() 
{ 
	if (RememberPain != 0)
	{
		return true;
	}
	else {
		return false;
	}
}

// the enemies melee attack
void AEnemyBaseClass::MeleeAttack()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector Location = GetActorLocation();
		FVector Offset = FVector(0.0f, 0.0f, 0.0f);

		FRotator ProjectileRotation = GetActorRotation();

		Location += Offset;

		GetWorld()->SpawnActor<AEnemyAttackBox>(EnemyAttackBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());

		float RandomValue = FMath::RandRange(0.8f, 1.2f);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, GetActorLocation(), 0.5f, RandomValue, 0.f, DamageAtt);
	}
}

// gets the distance to player
void AEnemyBaseClass::UpdateDistance()
{
	CurrentPlayerLocation = Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerLocation();

	DistanceVector = GetActorLocation() - CurrentPlayerLocation;
	DistanceToPlayer = DistanceVector.Size();
}

// When attacked by player
void AEnemyBaseClass::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// Physical attack
	if (OtherActor->IsA(APhysAttackBox::StaticClass()))
	{
		OtherActor->Destroy();
		HealthPoints -= DamageMelee;
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetTransform(), true);

		float RandomValue = FMath::RandRange(0.8f, 1.2f);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PhysImpactSound, GetActorLocation(), 0.5f, RandomValue, 0.f, DamageAtt);

		// Pushes the enemy back. They get slowed down for some time. (FORCE, DURATION).
		EnemyIsHit(1000.f, 1.5f);
	}

	if (OtherActor->IsA(AKnockbackSphere::StaticClass()))
	{
		// Pushes the enemy back. They get slowed down for some time. (FORCE, DURATION).
		EnemyIsHit(500.f, 1.f);
	}

	// Magic Projectile - WATER
	if (OtherActor->IsA(AMagicProjectile::StaticClass()))
	{
		OtherActor->Destroy();

		switch (Element)
		{
		case ElementsEnum::FIRE:
			// weak
			HealthPoints -= DamageMyWeakness;
			break;
		case ElementsEnum::WATER:
			// ok
			HealthPoints -= DamageMyEqual;
			break;
		case ElementsEnum::NATURE:
			// heal?
			HealthPoints -= DamageLeastEffective;
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("error - EnemyBaseClass - attacked"));
		}

		//Spiller av SFX.
		float RandomValue = FMath::RandRange(0.8f, 1.2f);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WaterImpactSound, GetActorLocation(), 1.f, RandomValue, 0.f, DamageAtt);

		//Spiller av VFX.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterHitFX, GetTransform(), true);
	}

	// Circle of thorns - NATURE
	if (OtherActor->IsA(ACircleOfThorns::StaticClass()))
	{
		switch (Element)
		{
		case ElementsEnum::WATER:
			// weak
			HealthPoints -= DamageMyWeakness;
			break;
		case ElementsEnum::NATURE:
			// ok
			HealthPoints -= DamageMyEqual;
			break;
		case ElementsEnum::FIRE:
			// heal?
			HealthPoints -= DamageLeastEffective;
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("error - EnemyBaseClass - attacked"));
		}

		EnemyIsHit(100.f, 3.f);
	}

	// Cone of fire - FIRE
	if (OtherActor->IsA(AConeOfFire::StaticClass()))
	{
		switch (Element)
		{
		case ElementsEnum::NATURE:
			// weak
			HealthPoints -= DamageMyWeakness;
			break;
		case ElementsEnum::FIRE:
			// ok
			HealthPoints -= DamageMyEqual;
			break;
		case ElementsEnum::WATER:
			// heal?
			HealthPoints -= DamageLeastEffective;
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("error - EnemyBaseClass - attacked"));
		}
	}

	//Spiller av SFX.
	float RandomValue = FMath::RandRange(0.8f, 1.2f);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnemyHurtSound, GetActorLocation(), 0.5f, RandomValue, 0.f, DamageAtt);

	// every time enemy is hurt it will follow player for 150 frames, no matter what
	RememberPain = 150.f;
	DeathCheck();
}

// Check if dead
void AEnemyBaseClass::DeathCheck()
{
	// DIE
	if (HealthPoints <= 0.f)
	{	
		// Lyd når de dør.
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnemyDeathSound, GetActorLocation());

		Destroy();

		if (	Cast<UFantasyGameInstance>(GetGameInstance())->GetCurrentLevel() != 3	) // do this unless it is the boss battle
		{
			GetWorld()->SpawnActor<ACrystalPawn>(CrystalBlueprint, GetActorLocation() + FVector(0.f, -30.f, 0.f), GetActorRotation());
		}
		

		// might spawn potion
		if (FMath::RandRange(0, 1) == 0)
		{
			//// randomize which potion is spawned
			if (FMath::RandRange(0, 2) == 0)
			{
				// spawn health potion
				GetWorld()->SpawnActor<AHealthPotion>(HealthBlueprint, GetActorLocation() + FVector(0.f, 30.f, 0.f), GetActorRotation());
			}
			else
			{
				// spawn mana potion
				GetWorld()->SpawnActor<AManaPotion>(ManaBlueprint, GetActorLocation() + FVector(0.f, 30.f, 0.f), GetActorRotation());
			}
		}
	}
	else
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Sett inn alternativ for damage lyder.
	}
}

void AEnemyBaseClass::EnemyIsHit(float force, float duration)
{
	// Pushes back the enemy.
	// FVector PlayerLocation = Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerLocation();

	FVector KnockbackVector = GetActorLocation() - CurrentPlayerLocation;
	KnockbackVector.Normalize();

	LaunchCharacter((KnockbackVector * force) + FVector(0.f, 0.f, 20.f), false, false);

	GetCharacterMovement()->MaxWalkSpeed = (MovementSpeed / 4);

	GetWorldTimerManager().SetTimer(SlowdownTimerHandle, this, &AEnemyBaseClass::SlowdownOver, duration, false);
}

void AEnemyBaseClass::SlowdownOver()
{
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

	GetWorld()->GetTimerManager().ClearTimer(SlowdownTimerHandle);
}

// line trace to check if enemy sees player, or if line of sight is blocked
bool AEnemyBaseClass::CanSeePlayer()
{
	if (GetWorld()->GetFirstPlayerController()->GetCharacter())
	{

		// Updates DistanceToPlayer
		UpdateDistance();

		if (DistanceToPlayer < 900.f)
		{
			FHitResult hitResult;
			FVector MyLocation = GetActorLocation();
			CurrentPlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
			FCollisionQueryParams collisionParams = FCollisionQueryParams();
			collisionParams.AddIgnoredActor(this);

			GetWorld()->LineTraceSingleByChannel(hitResult, MyLocation, CurrentPlayerLocation, ECC_Visibility, collisionParams); ////////

			if (hitResult.bBlockingHit)
			{
				return false;
			}
			else
			{
				// Enemy physical attack. - should move to controller ///////////
				if (DistanceToPlayer < 100.f)
				{
					++AttackTimer;
					if (AttackTimer > 20.f)
					{
						AEnemyBaseClass::MeleeAttack();
						AttackTimer = 0.f;
					}
				}
				return true;
			}
		}
		else
		{
			// player not close enough, so no point in running the other tests
			return false;
		}

	FHitResult hitResult;
	FVector MyLocation = GetActorLocation();
	FCollisionQueryParams collisionParams = FCollisionQueryParams();
	collisionParams.AddIgnoredActor(this);
	}
	else
	{
		// there is no player available, so more tests could crash the engine
		return false;
	}
}

void AEnemyBaseClass::PainForgetter()
{
	RememberPain -= 1.f;
	if (RememberPain < 0.1f)
	{
		RememberPain = 0;
	}
}