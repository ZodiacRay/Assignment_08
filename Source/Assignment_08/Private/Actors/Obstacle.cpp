// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Obstacle.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	int32 MeshNum = Meshes.Num();
	if (MeshNum == 0) return;
	
	int32 MeshIndex = FMath::RandRange(0, MeshNum - 1);
	
	StaticMesh->SetStaticMesh(Meshes[MeshIndex]);
}



