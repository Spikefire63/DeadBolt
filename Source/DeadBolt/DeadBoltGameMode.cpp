// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeadBoltGameMode.h"
#include "DeadBoltCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeadBoltGameMode::ADeadBoltGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
