// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

class UStaticMesh; 
class UStaticMeshComponent; 

UCLASS()
class ASSIGNMENT_08_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	TArray<UStaticMesh*> Meshes; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	UStaticMeshComponent* StaticMesh;
	
};
