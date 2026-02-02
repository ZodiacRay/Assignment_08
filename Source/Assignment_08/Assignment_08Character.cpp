// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment_08Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include"UI/CharacterStateTextWidget.h"
#include "Kismet/GameplayStatics.h"

AAssignment_08Character::AAssignment_08Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	StateWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StateWidgetComponent"));
	StateWidgetComponent->SetupAttachment(RootComponent);
	StateWidgetComponent->SetVisibility(false); 
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAssignment_08Character::BeginPlay()
{
	Super::BeginPlay();
}

void AAssignment_08Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

#pragma region Movement Functions
void AAssignment_08Character::AddSpeedMultiplier(float Amount)
{
	CurrentSpeedMultiplier += Amount;
	ApplyFinalSpeed();
}

void AAssignment_08Character::RemoveSpeedMultiplier(float Amount)
{
	CurrentSpeedMultiplier -= Amount;
	ApplyFinalSpeed();
}

void AAssignment_08Character::ApplyFinalSpeed()
{
	
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * CurrentSpeedMultiplier;
}
#pragma endregion

#pragma region UI Functions

void AAssignment_08Character::UpdateStateWidget(FText State)
{
	if (StateWidgetComponent == nullptr) return; 
	
	ToggleStateWidgetVisibility(true); 
	
	UUserWidget* UW = StateWidgetComponent->GetUserWidgetObject();
	if (UW == nullptr) return; 
	
	UCharacterStateTextWidget* StateTextWidget = Cast<UCharacterStateTextWidget>(UW);
	if (StateTextWidget)
	{
		StateTextWidget->UpdateTextBlock(State); 
		UE_LOG(LogTemp, Warning, TEXT("State Changed.")); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail to Change State"));
	}
}

void AAssignment_08Character::ClearStateWidget()
{
	if (StateWidgetComponent == nullptr) return; 
	
	ToggleStateWidgetVisibility(false); 
	
	UCharacterStateTextWidget* StateTextWidget = Cast<UCharacterStateTextWidget>(StateWidgetComponent->GetUserWidgetObject());
	if (StateTextWidget)
	{
		StateTextWidget->UpdateTextBlock(FText::FromString("")); 
	}
}


void AAssignment_08Character::ToggleStateWidgetVisibility(bool bEnabled)
{
	if (StateWidgetComponent)
	{
		StateWidgetComponent->SetVisibility(bEnabled);
	}
}
#pragma endregion 


#pragma region Attribute Functions 
void AAssignment_08Character::BroadcastHealthChanged()
{
	if (OnHealthChanged.IsBound())
	{
		float Ratio = CurrentHealth / MaxHealth;
		OnHealthChanged.Broadcast(Ratio);
	}
}

float AAssignment_08Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); 
	
	if (CurrentPlayerState == ECharacterstatus::Invincibility) return 0.f; 
	
	CurrentHealth = FMath::Clamp(CurrentHealth - ActualDamage, 0, MaxHealth);
	
	if (CurrentHealth <= 0.f)
	{
		Die();
	}	

	BroadcastHealthChanged(); 
	
	return ActualDamage; 
}

void AAssignment_08Character::AddHealth(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0, MaxHealth);
	BroadcastHealthChanged(); 
}


void AAssignment_08Character::Die()
{
	if (CurrentHealth > 0.f) return; 
	
	if (DeathMontage)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f); 
		float Duration = PlayAnimMontage(DeathMontage,1.f);
		
		GetCharacterMovement()->DisableMovement(); 
		
		TWeakObjectPtr<AAssignment_08Character> WeakThis = this;
		GetWorld()->GetTimerManager().SetTimer(
		DeathTimerHandle,
		[WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->GetMesh()->SetSimulatePhysics(true);
				WeakThis->GetMesh()->bNoSkeletonUpdate = true;
				
				if(WeakThis->OnCharacterDeath.IsBound())
				{
					WeakThis->OnCharacterDeath.Broadcast(WeakThis->IsDead); 
				}
			}
		},
		Duration - 0.2f,
		false
		);
	}
	
}


#pragma endregion
