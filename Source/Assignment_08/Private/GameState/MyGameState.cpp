// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/MyGameState.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Assignment_08PlayerController.h"
#include "Assignment_08Character.h"
#include "GameState/MyGameInstance.h"
#include "UI/PlayerHUD.h"

AMyGameState::AMyGameState()
{

}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up Kill Z  
	AWorldSettings* WorldSettings = GetWorld()->GetWorldSettings();
	if (WorldSettings)
	{
		WorldSettings->KillZ = -1000.f;
	}
	
	// Get Current LevelInfo  
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()); 
	if (GI)
	{
		CurrentLevelIndex = GI->CurrentLevelIndex;
	}
	MaxLevels = LevelMapNames.Num();
	
	UpdateHUD();
	StartLevel(); 
	
	// HUD Update Timer 
	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AMyGameState::UpdateHUD,
		0.1f,
		true
	);
}


void AMyGameState::StartLevel()
{
	if (LevelDuration.IsValidIndex(CurrentLevelIndex))
	{
		// Level Timer 
		GetWorldTimerManager().SetTimer(
			LevelTimerHandle,
			this,
			&AMyGameState:: EndLevel,
			LevelDuration[CurrentLevelIndex],
			false
		);
	}
	
	// Bind Character Alive 
	ACharacter* Char = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Char == nullptr) return; 
	AAssignment_08Character* Character = Cast<AAssignment_08Character>(Char);
	if (Character == nullptr) return;
	
	Character->OnCharacterDeath.AddDynamic(this, &AMyGameState::GameOver);
	
}

void AMyGameState::EndLevel()
{
	// Clear Current Level Timer 
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	GetWorldTimerManager().ClearTimer(HUDUpdateTimerHandle);
	
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GameInstance")); 
		return; 
	}
	
	// Increase Level Index 
	GI->CurrentLevelIndex++;
	CurrentLevelIndex = GI->CurrentLevelIndex; 
	
	// Check Is Final Level 
	if (CurrentLevelIndex >= MaxLevels)
	{
		GameClear(); 
		return;
	}
	
	// Open NextLevel 
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	
	
}

void AMyGameState::GameOver(bool PlayerDead)
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	GetWorldTimerManager().ClearTimer(HUDUpdateTimerHandle);
	
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
	
	// Pause Game 
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.f,
			FColor::Red,
			FString::Printf(TEXT("GameOver!"))
		);
	}
}

void AMyGameState::GameClear()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
}

void AMyGameState::UpdateHUD()
{
	AAssignment_08PlayerController* PC =Cast<AAssignment_08PlayerController> (GetWorld()->GetFirstPlayerController()); 
	if (PC == nullptr) return; 
	
	UPlayerHUD* HUD = Cast<UPlayerHUD>(PC->GetHUDInstance()); 
	if (HUD == nullptr) return;

	if (LevelDuration.IsValidIndex(CurrentLevelIndex))
	{
		// Get Time Ratio 
		float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
		float Duration = LevelDuration[CurrentLevelIndex];
		float TimeRatio = Duration > 0.f ? RemainingTime / Duration : 0.f;
		
		// Get Current Level Info 
		FText LevelText = FText::Format(
			FText::FromString("Level: {0}"),
					FText::AsNumber(CurrentLevelIndex +1)
		); 
		
		// Update HUD
		HUD->UpdateTimeBar(TimeRatio, LevelText);
	}
}
