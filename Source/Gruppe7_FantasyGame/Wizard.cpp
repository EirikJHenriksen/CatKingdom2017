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
	
	VoiceIsActive = true;

	cloudIsActive = false;
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetBossFightActive() && !WizardIntroDone)
	{	
		WizardIntroDone = true;
		GetWorldTimerManager().SetTimer(IntroTimerHandle, this, &AWizard::IntroDialogue, 7.f, false);
	}

	// Plays dialogue if it fits the situation.
	DialogueCheck();

	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetMana() <= 0.5f && !cloudIsActive)
	{
		cloudIsActive = true;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Player needs mana!"));

		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWizard::Spawn, FMath::RandRange(RandomMin, RandomMax), false);
	}
}

void AWizard::IntroDialogue()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardIntro, GetActorLocation());
	GetWorld()->GetTimerManager().ClearTimer(IntroTimerHandle);

	VoiceIsActive = false;
}

void AWizard::Spawn()
{
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("MANA IS SPAWNED!"));

	GetWorld()->SpawnActor<AWizardCloud>(WizardCloudBlueprint, GetActorLocation() + GetActorForwardVector() * 200.f, GetActorRotation());
	
	if (!VoiceIsActive && !Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerIsDead())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardNotifySpawn, GetActorLocation());
	}

	cloudIsActive = false;
}

void AWizard::DialogueCheck()
{	
	if (Cast<UFantasyGameInstance>(GetGameInstance())->GetPlayerIsDead() && !VoiceIsActive)
	{	
		VoiceIsActive = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardPlayerDead, GetActorLocation(), 1.f, 1.f);
	}
	else if (Cast<UFantasyGameInstance>(GetGameInstance())->GetBossAttack() && !VoiceIsActive)
	{	
		VoiceIsActive = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WizardWarning, GetActorLocation(), 1.f, 1.f);
	}

	GetWorldTimerManager().SetTimer(VoiceFinishedTimerHandle, this, &AWizard::VoiceIsFinished, 2.f, false);
}

void AWizard::VoiceIsFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(VoiceFinishedTimerHandle);

	VoiceIsActive = false;
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

