// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe7_FantasyGame.h"
#include "Wizard.h"
#include "WizardCloud.h"
#include "FantasyGameInstance.h"


// Sets default values
AWizard::AWizard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();
	
	VoiceIsActive = false;

	cloudIsActive = false;
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetBossFightActive() && !WizardIntroDone)
	{	
		VoiceIsActive = true;
		WizardIntroDone = true;
		GetWorldTimerManager().SetTimer(IntroTimerHandle, this, &AWizard::IntroDialogue, 7.f, false);
	}

	// Plays dialogue if it fits the situation.
	DialogueCheck();

	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetMana() <= 0.5f && !cloudIsActive && !Cast<UFantasyGameInstance>(GetGameInstance())->GetBossIsDead())
	{
		cloudIsActive = true;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Player needs mana!"));

		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWizard::Spawn, FMath::RandRange(RandomMin, RandomMax), false);
	}

	if (QueueingSound)
	{
		SpawnedManaAudio();
		QueueingSound = false;
	}
}

void AWizard::IntroDialogue()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardIntro, GetActorLocation());
	GetWorld()->GetTimerManager().ClearTimer(IntroTimerHandle);

	GetWorldTimerManager().SetTimer(VoiceFinishedTimerHandle, this, &AWizard::VoiceIsFinished, 7.f, false);
}

void AWizard::Spawn()
{
	GetWorld()->SpawnActor<AWizardCloud>(WizardCloudBlueprint, GetActorLocation() + GetActorForwardVector() * 200.f, GetActorRotation());
	
		
	QueueingSound = true;
	

	// Sets cooldown, before it can be spawned again.
	GetWorldTimerManager().SetTimer(SpawnCooldownTimerHandle, this, &AWizard::SpawnCooldown, 15.f, false);
}

void AWizard::SpawnCooldown()
{
	cloudIsActive = false;
}

void AWizard::DialogueCheck()
{	
	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerIsDead() && !VoiceIsActive)
	{	
		VoiceIsActive = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardPlayerDead, GetActorLocation(), 1.f, 1.f);
	}
	
	//// 2/3 chance to play this sounde, because testing found it could be played too often, if NightNight shoots often
	//if (Cast<UFantasyGameInstance>(GetGameInstance())->GetBossAttack() && !VoiceIsActive && !Cast<UFantasyGameInstance>(GetGameInstance())->GetBossIsDead() && (FMath::RandRange(0, 2) > 0))
	//{	
	//	VoiceIsActive = true;
	//	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardWarning, GetActorLocation(), 1.f, 1.f);
	//	GetWorldTimerManager().SetTimer(VoiceFinishedTimerHandle, this, &AWizard::VoiceIsFinished, 4.f, false);
	//}

	//if (Cast<UFantasyGameInstance>(GetGameInstance())->GetBossIsDead() && !VoiceIsActive)
	//{
	//	VoiceIsActive = true;
	//	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardWin, GetActorLocation(), 1.f, 1.f);
	//}
}

void AWizard::VoiceIsFinished()
{	
	VoiceIsActive = false;
	GetWorld()->GetTimerManager().ClearTimer(VoiceFinishedTimerHandle);
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWizard::SpawnedManaAudio()
{
	VoiceIsActive = true;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardNotifySpawn, GetActorLocation());
	GetWorldTimerManager().SetTimer(VoiceFinishedTimerHandle, this, &AWizard::VoiceIsFinished, 3.f, false);
}
