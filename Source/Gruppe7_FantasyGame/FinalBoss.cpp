// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "FinalBoss.h"
#include "MagicProjectile.h"
#include "ConeOfFire.h"
#include "CircleOfThorns.h"
#include "PhysAttackBox.h"
#include "BossSpellFire.h"
#include "EnemyBaseClass.h"
#include "Gruppe7_FantasyGameCharacter.h"
#include "FantasyGameInstance.h"


// Sets default values
AFinalBoss::AFinalBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFinalBoss::OnOverlap);
}

// Called when the game starts or when spawned
void AFinalBoss::BeginPlay()
{
	Super::BeginPlay();

	Health = 1.f;

	isDoingSomething = false;

	canBeHurt = false;

	firstTeleport = true;

	firstTeleportOver = false;

	PlayerIsDead = false;

	BossIsAnnoyed = false;

	//////////////////////////////
	// Voice.
	VoiceIsActive = true;

	//////////////////////////////
	// Animation.
	animStoppedAttacking = true;
	animIsAttacking = false;

	animStoppedTeleporting = true;
	animIsTeleporting = false;
	
	animStoppedSummoning = true;
	animIsSummoning = false;
}

// Called every frame
void AFinalBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Gets variable from gameInstance class.
	fightInProgress = Cast<UFantasyGameInstance>(GetGameInstance())->GetBossFightActive();

	// Keeps track of the players location.
	CurrentPlayerLocation = Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerLocation();

	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerIsDead() && !BossWinVoicePlayed)
	{	
		BossWinVoicePlayed = true;
		PlayerIsDead = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossWin, GetActorLocation(), 1.f);
	}

	if (Health < 0.5f && !BossIsAnnoyed && !VoiceIsActive)
	{	
		BossIsAnnoyed = true;
		VoiceIsActive = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossAnnoyed, GetActorLocation(), 1.f);

		GetWorldTimerManager().SetTimer(VoiceIsActiveTimerHandle, this, &AFinalBoss::TeleportFirstStage, 3.f, false);
	}
		
	// Turns boss towards player.
	if (!IsDying)
	{	
		// Updates LookVector
		UpdateDirection();

		SetActorRotation(FRotator(0.f, LookVector.Rotation().Yaw, 0.f));
	}
	
	if (fightInProgress && !IsDying)
	{	
		if (firstTeleport)
		{	
			GetWorldTimerManager().SetTimer(FirstTeleportTimerHandle, this, &AFinalBoss::TeleportFirstStage, 8.f, false);

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossIntro, GetActorLocation(), 1.f);

			firstTeleport = false;

			TheActionInt = FMath::RandRange(0, 3);
		}
		else if (!isDoingSomething && firstTeleportOver)
		{	
			isDoingSomething = true;
			
			// Makes the boss take an action.
			DoSomething();
		}
	}
}

void AFinalBoss::DoSomething()
{	
	switch (TheActionInt)
	{
	default:
		break;
	case 0:
		RandomActionTime = FMath::RandRange(RandomMin, RandomMax);

		GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &AFinalBoss::TeleportFirstStage, RandomActionTime, false);
		break;
	case 1:
		RandomActionTime = FMath::RandRange(RandomMin, RandomMax);

		GetWorldTimerManager().SetTimer(SummonTimerHandle, this, &AFinalBoss::SummonFirstStage, RandomActionTime, false);
		break;
	case 2:
		RandomActionTime = FMath::RandRange(RandomMin, RandomMax);

		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AFinalBoss::AttackFirstStage, RandomActionTime, false);
		break;
	case 3:
		RandomActionTime = FMath::RandRange(RandomMin, RandomMax);

		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AFinalBoss::AttackFirstStage, RandomActionTime, false);
		break;
	}

	TheActionInt = FMath::RandRange(0, 3);
}

// gets the distance to player
void AFinalBoss::UpdateDirection()
{
	LookVector = CurrentPlayerLocation - GetActorLocation();
}

// Called to bind functionality to input
void AFinalBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFinalBoss::VoiceIsFinished()
{
	VoiceIsActive = false;
	GetWorld()->GetTimerManager().ClearTimer(VoiceIsActiveTimerHandle);
}

void AFinalBoss::SetRandomElement()
{
	RandomElement = FMath::RandRange(0, 2);

	if (RandomElement == Element)
	{
		SetRandomElement();
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("RETRY TO GET ELEMENT!!!"));
	}
}

void AFinalBoss::TeleportFirstStage()
{	
	// Makes sure boss doesn't teleport to same spot as he's currently at.
	SetRandomElement();

	animIsTeleporting = true;
	animStoppedTeleporting = false;

	// This if test sets up some variables so the encounter goes from "intro" mode to the actual combat mode.
	if (!canBeHurt)
	{
		canBeHurt = true;

		GetWorld()->GetTimerManager().ClearTimer(FirstTeleportTimerHandle);

		// Plays the last piece of intro dialouge.
		GetWorldTimerManager().SetTimer(IntroPartTwoTimerHandle, this, &AFinalBoss::IntroPartTwo, 12.f, false);
	}

	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AFinalBoss::TeleportSecondStage, 2.7f, false);
}

void AFinalBoss::TeleportSecondStage()
{	
	//SFX.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), TeleportSound, GetActorLocation(), 1.f);
	//VFX.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportFX, GetTransform(), true);

	switch (RandomElement)
	{
	default:
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("SOMETHING WENT WRONG WITH BOSS TELEPORT! FUNCTION: Teleport()"));
		break;
	case 0:
		Element = 0;
		SetActorLocation(FVector(FireX, FireY, FireZ), false);
		break;
	case 1:
		Element = 1;
		SetActorLocation(FVector(WaterX, WaterY, WaterZ), false);
		break;
	case 2:
		Element = 2;
		SetActorLocation(FVector(NatureX, NatureY, NatureZ), false);
		break;
	}

	GetWorld()->GetTimerManager().ClearTimer(TeleportTimerHandle);

	if (!firstTeleportOver)
	{
		firstTeleportOver = true;
	}

	animIsTeleporting = false;
	animStoppedTeleporting = true;

	isDoingSomething = false;
}

void AFinalBoss::AttackFirstStage()
{	
	animIsAttacking = true;
	animStoppedAttacking = false;

	// Notifies game instance of attack so the wizard can warn the player.
	Cast<UFantasyGameInstance>(GetGameInstance())->SetBossAttack(true);

	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);

	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &AFinalBoss::AttackSecondStage, 1.f, false);
}

void AFinalBoss::AttackSecondStage()
{	
	UWorld* World = GetWorld();
	if (World && !PlayerIsDead)
	{
		GetWorld()->SpawnActor<ABossSpellFire>(SpellFireBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), MagicAttackSound, GetActorLocation());
	}

	GetWorld()->GetTimerManager().ClearTimer(AnimAttackTimerHandle);

	Cast<UFantasyGameInstance>(GetGameInstance())->SetBossAttack(false);

	animIsAttacking = false;
	animStoppedAttacking = true;

	isDoingSomething = false;
}

void AFinalBoss::SummonFirstStage()
{
	animIsSummoning = true;
	animStoppedSummoning = false;

	GetWorld()->GetTimerManager().ClearTimer(SummonTimerHandle);

	GetWorldTimerManager().SetTimer(AnimSummonTimerHandle, this, &AFinalBoss::SummonSecondStage, 1.5f, false);
}

void AFinalBoss::SummonSecondStage()
{
	switch (Element)
	{
	default:
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("SOMETHING WENT WRONG WITH SUMMONS! FUNCTION: SummonEnemy()"));
		break;
	case 0:
		//Spiller av VFX.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SummonFX, FTransform(GetActorRotation().Quaternion(), FVector(SpawnX, SpawnY, SpawnZ), FVector(1.f, 1.f, 1.f)), true);
		GetWorld()->SpawnActor<AEnemyBaseClass>(FireEnemyBlueprint, FVector(SpawnX, SpawnY, SpawnZ), GetActorRotation());
		break;
	case 1:
		//Spiller av VFX.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SummonFX, FTransform(GetActorRotation().Quaternion(), FVector(SpawnX, SpawnY, SpawnZ), FVector(1.f, 1.f, 1.f)), true);
		GetWorld()->SpawnActor<AEnemyBaseClass>(WaterEnemyBlueprint, FVector(SpawnX, SpawnY, SpawnZ), GetActorRotation());
		break;
	case 2:
		//Spiller av VFX.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SummonFX, FTransform(GetActorRotation().Quaternion(), FVector(SpawnX, SpawnY, SpawnZ), FVector(1.f, 1.f, 1.f)), true);
		GetWorld()->SpawnActor<AEnemyBaseClass>(NatureEnemyBlueprint, FVector(SpawnX, SpawnY, SpawnZ), GetActorRotation());
		break;
	}

	GetWorld()->GetTimerManager().ClearTimer(AnimSummonTimerHandle);
	animIsSummoning = false;
	animStoppedSummoning = true;

	isDoingSomething = false;
}

void AFinalBoss::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// Physical attack
	if (OtherActor->IsA(APhysAttackBox::StaticClass()))
	{
		OtherActor->Destroy();
		ResistAttack();
	}

	// Magic Projectile - WATER
	if (OtherActor->IsA(AMagicProjectile::StaticClass()))
	{	
		OtherActor->Destroy();

		//Spiller av VFX.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WaterHitFX, GetTransform(), true);
		//SFX.
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WaterImpactSound, GetActorLocation(), 1.f);

		if (canBeHurt && Element == 0)
		{	
			Health -= 0.04f;

			// Camera shake.
			Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ClientPlayCameraShake(CameraShake, 1.f);

			if (!VoiceIsActive)
			{
				VoiceIsActive = true;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossHurt, GetActorLocation());

				DeathCheck();

				GetWorldTimerManager().SetTimer(VoiceIsActiveTimerHandle, this, &AFinalBoss::VoiceIsFinished, 1.5f, false);
			}
		}
		else
		{
			ResistAttack();
		}
	}

	// Circle of thorns - NATURE
	if (OtherActor->IsA(ACircleOfThorns::StaticClass()))
	{
		if (canBeHurt && Element == 1)
		{
			Health -= 0.04f;

			// Camera shake.
			Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ClientPlayCameraShake(CameraShake, 1.f);

			if (!VoiceIsActive)
			{
				VoiceIsActive = true;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossHurt, GetActorLocation());

				DeathCheck();

				GetWorldTimerManager().SetTimer(VoiceIsActiveTimerHandle, this, &AFinalBoss::VoiceIsFinished, 1.5f, false);
			}
		}
		else
		{
			ResistAttack();
		}
	}

	// Cone of fire - FIRE
	if (OtherActor->IsA(AConeOfFire::StaticClass()))
	{
		if (canBeHurt && Element == 2)
		{
			Health -= 0.03f;

			// Camera shake.
			Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ClientPlayCameraShake(CameraShake, 1.f);

			if (!VoiceIsActive)
			{	
				VoiceIsActive = true;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossHurt, GetActorLocation());

				DeathCheck();

				GetWorldTimerManager().SetTimer(VoiceIsActiveTimerHandle, this, &AFinalBoss::VoiceIsFinished, 1.5f, false);
			}
		}
		else
		{
			ResistAttack();
		}
	}
}

void AFinalBoss::IntroPartTwo()
{	
	// Previous part is within the TeleportFirstStage() function.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossIntroTwo, GetActorLocation(), 1.f);
	GetWorld()->GetTimerManager().ClearTimer(IntroPartTwoTimerHandle);

	GetWorldTimerManager().SetTimer(VoiceIsActiveTimerHandle, this, &AFinalBoss::VoiceIsFinished, 2.f, false);
}

void AFinalBoss::ResistAttack()
{	
	//SFX.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FailSparkSound, GetActorLocation(), 1.f);
	//VFX.
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFailFX, GetTransform(), true);

	if (!VoiceIsActive)
	{	
		VoiceIsActive = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossLaugh, GetActorLocation(), 1.f);

		GetWorldTimerManager().SetTimer(VoiceIsActiveTimerHandle, this, &AFinalBoss::VoiceIsFinished, 3.f, false);
	}
}

void AFinalBoss::IsNowDead()
{	
	IsDead = true;
	GetWorld()->GetTimerManager().ClearTimer(AnimDyingTimerHandle);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossDeathScream, GetActorLocation(), 1.f);

	GetWorldTimerManager().SetTimer(BossDeadTimerHandle, this, &AFinalBoss::GameWon, 8.f, false);
}

void AFinalBoss::DeathCheck()
{
	if (Health <= 0.f && !IsDying)
	{	
		animStoppedAttacking = true;
		animIsAttacking = false;

		animStoppedTeleporting = true;
		animIsTeleporting = false;

		animStoppedSummoning = true;
		animIsSummoning = false;

		GetWorld()->GetTimerManager().ClearTimer(TeleportTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(SummonTimerHandle);

		FRotator DeathRotate = LookVector.Rotation();

		SetActorRotation(FRotator(0.f, DeathRotate.Yaw, 0.f));

		IsDying = true;

		if (!IsDead)
		{	
			Cast<UFantasyGameInstance>(GetGameInstance())->SetBossIsDead(true);

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), BossDefeatComplain, GetActorLocation(), 1.f);

			GetWorldTimerManager().SetTimer(AnimDyingTimerHandle, this, &AFinalBoss::IsNowDead, 5.2f, false);
		}
	}
}

void AFinalBoss::GameWon()
{
	// Lets the game know that the game is won. 
	Cast<UFantasyGameInstance>(GetGameInstance())->SetGameIsWon(true);
	
	GetWorld()->GetTimerManager().ClearTimer(BossDeadTimerHandle);
}