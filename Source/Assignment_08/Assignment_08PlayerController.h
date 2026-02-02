// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Assignment_08PlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UUserWidget; 

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);



UCLASS(abstract)
class AAssignment_08PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, Category="Input")
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SetDestinationTouchAction;

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	/** Set to true if we're using touch input */
	uint32 bIsTouch : 1;

	/** Saved location of the character movement destination */
	FVector CachedDestination;

	/** Time that the click input has been pressed */
	float FollowTime = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	
	UPROPERTY(EditAnywhere, Category="Widget")
	UUserWidget* HUDInstance; 

public:

	/** Constructor */
	AAssignment_08PlayerController();
	
	virtual void BeginPlay() override;
	
	FORCEINLINE UUserWidget* GetHUDInstance() const { return HUDInstance; }

protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	/** Input handlers */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

};


