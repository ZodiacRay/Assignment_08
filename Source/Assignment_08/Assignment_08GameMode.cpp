// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment_08GameMode.h"
#include "Assignment_08Character.h"
#include "Assignment_08PlayerController.h"
#include "GameState/MyGameState.h"

AAssignment_08GameMode::AAssignment_08GameMode()
{
	
	DefaultPawnClass = AAssignment_08Character::StaticClass();
	PlayerControllerClass = AAssignment_08PlayerController::StaticClass();
	
	GameStateClass = AMyGameState::StaticClass();
	
}
