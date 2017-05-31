// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Gruppe7_FantasyGame.h"
#include "Gruppe7_FantasyGameGameMode.h"
#include "Gruppe7_FantasyGameCharacter.h"

AGruppe7_FantasyGameGameMode::AGruppe7_FantasyGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/FantasyGameCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
