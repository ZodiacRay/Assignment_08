// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Assignment_08Character.generated.h"

UENUM()
enum ECharacterstatus : uint8
{
	Idle UMETA(DisplayName="Idle"),
	Slowed UMETA(DisplayName="Slowed"),
	Fasted UMETA(DisplayName="Fasted"),
	AirBorned UMETA(DisplayName="Airborne Born"),
	Root UMETA(DisplayName="Root"),
	Invincibility UMETA(DisplayName="Invincibility"),
};


class UWidgetComponent; 

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateOnHealthChanged, float); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDeath, bool, bIsDead);

UCLASS(abstract)
class AAssignment_08Character : public ACharacter
{
	GENERATED_BODY()

private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:

	/** Constructor */
	AAssignment_08Character();

	/** Initialization */
	virtual void BeginPlay() override;

	/** Update */
	virtual void Tick(float DeltaSeconds) override;

	/** Returns the camera component **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns the Camera Boom component **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
public:
	FORCEINLINE float GetBaseSpeed() const { return BaseSpeed; } 
	
	void AddSpeedMultiplier(float Amount); 
	
	
	void RemoveSpeedMultiplier(float Amount);

	void ApplyFinalSpeed();
#pragma region UI Functions 
public:
	void UpdateStateWidget(FText State); 
	
	void ClearStateWidget();
	
protected:
	void ToggleStateWidgetVisibility(bool bEnabled); 


#pragma endregion
	
	
#pragma region Attribute Functions
public:
	void BroadcastHealthChanged(); 

	virtual float TakeDamage( float DamageAmount, FDamageEvent const& DamageEvent, 
		AController* EventInstigator, AActor* DamageCauser) override;
	
	void AddHealth(float Amount);
	
	void Die(); 
	
	ECharacterstatus GetCurrentPlayerState() const {return CurrentPlayerState;}
	void SetCurrentPlayerState(ECharacterstatus NewState) {CurrentPlayerState = NewState;}

#pragma endregion
	
	
#pragma region Attribute 
public:
	FDelegateOnHealthChanged OnHealthChanged; 
	
	FOnCharacterDeath OnCharacterDeath;
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UWidgetComponent* StateWidgetComponent; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;
	
	bool IsDead = false;
	
	ECharacterstatus CurrentPlayerState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	UAnimMontage* DeathMontage;
	
	FTimerHandle DeathTimerHandle;
#pragma endregion 
	
#pragma region Movement Variables
protected:
	float BaseSpeed = 600.f;
	
	float CurrentSpeedMultiplier = 1.0f;
	
#pragma endregion
	
	
	
};

