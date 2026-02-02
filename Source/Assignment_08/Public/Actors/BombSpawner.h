// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SpawnVolume.h"
#include "BombSpawner.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_08_API ABombSpawner : public ASpawnVolume
{
	GENERATED_BODY()
public:
	ABombSpawner(); 
	
	
	virtual void BeginPlay() override; 
	
	void SpawnBomb(); 
	
protected:
	FTimerHandle SpawnTimerHandle; 
	

	
};
