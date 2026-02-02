// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_08_API AMyGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMyGameState(); 
	
	virtual void BeginPlay() override;
	
	void StartLevel();
	void EndLevel(); 
	UFUNCTION()
	void GameOver(bool PlayerDead);
	void GameClear(); 
	
	void UpdateHUD(); 
	
public:
	
	FTimerHandle HUDUpdateTimerHandle;
	FTimerHandle LevelTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level" )
	TArray<float> LevelDuration;  
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;
};
