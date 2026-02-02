// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Assignment_08GameMode.generated.h"

/**
 *  Simple Game Mode for a top-down perspective game
 *  Sets the default gameplay framework classes
 *  Check the Blueprint derived class for the set values
 */
UCLASS(abstract)
class AAssignment_08GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	/** Constructor */
	AAssignment_08GameMode();
};



