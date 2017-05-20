// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CrystalAIController.generated.h"

/**
 * 
 */
UCLASS()
class GRUPPE7_FANTASYGAME_API ACrystalAIController : public AAIController
{
	GENERATED_BODY()
	
public:
		//virtual void Possess(APawn *InPawn) override;

		virtual void Tick(float DeltaTime) override;
	
	
};
