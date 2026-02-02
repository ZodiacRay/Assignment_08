// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BombSpawner.h"

ABombSpawner::ABombSpawner()
{
	bShouldLoop = true; 
	bShouldRandomRoation = true; 
}

void ABombSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ABombSpawner::SpawnBomb()
{
	if ( FItemSpawnRow* SelectedRow = GetRandomItem() )
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
	
		}
	}
}
