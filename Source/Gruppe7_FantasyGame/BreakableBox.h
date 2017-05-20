// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BreakableBox.generated.h"

UCLASS()
class GRUPPE7_FANTASYGAME_API ABreakableBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableBox();

	/////////////////////////////////////////////////////////
	// Objects that can fall out of box can be set in editor.
	UPROPERTY(EditAnywhere, Category = "Contents of box")
		TSubclassOf<class AManaPotion> ManaPotionBlueprint;
	
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox;

	// Variables.
	float Health;

	float RandomNumber;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

public:	
	void RecieveDamage(float Damage);

};
