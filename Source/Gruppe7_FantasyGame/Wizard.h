// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Wizard.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API AWizard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWizard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void IntroDialogue();

	void Spawn();

	void SpawnCooldown();

	/////////////////////////////////////////
	// SFX.
	UPROPERTY(EditAnywhere)
		USoundBase* WizardSpellSound;

	/////////////////////////////////////////
	// Voice.
	UPROPERTY(EditAnywhere)
		USoundBase* WizardIntro;

	UPROPERTY(EditAnywhere)
		USoundBase* WizardNotifySpawn;

	UPROPERTY(EditAnywhere)
		USoundBase* WizardWarning;

	UPROPERTY(EditAnywhere)
		USoundBase* WizardPlayerDead;

	UPROPERTY(EditAnywhere)
		USoundBase* WizardWin;

	bool VoiceIsActive;

	bool WizardIntroDone;

	void DialogueCheck();

	void VoiceIsFinished();

	void SpawnedManaAudio();

	FTimerHandle IntroTimerHandle;

	FTimerHandle VoiceFinishedTimerHandle;

	/////////////////////////////////////////
	// SPAWNING.
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AWizardCloud> WizardCloudBlueprint;

	FTimerHandle SpawnCooldownTimerHandle;

	// SPAWN LOCATION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana Cloud SPAWN")
		float SpawnX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana Cloud SPAWN")
		float SpawnY = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mana Cloud SPAWN")
		float SpawnZ = 0;

	// SPAWN TIMERS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn timers")
		float RandomMin = 6.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn timers")
		float RandomMax = 12.f;

	FTimerHandle SpawnTimerHandle;

	bool cloudIsActive;

	bool QueueingSound = false;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
