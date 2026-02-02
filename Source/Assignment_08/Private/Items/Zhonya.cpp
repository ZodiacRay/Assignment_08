// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Zhonya.h"
#include "Assignment_08Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundWave.h"

void AZhonya::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	// 1. Check Character and Movement 
	AAssignment_08Character* Character = Cast<AAssignment_08Character>(Activator);
	if (Character == nullptr) return ; 
	
	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	if (MovementComponent == nullptr) return ;
 
	// 2. Item Logic 
 	MovementComponent->SetMovementMode(MOVE_None);
	Character->GetMesh()->bNoSkeletonUpdate = true; 
	Character->SetCurrentPlayerState(ECharacterstatus::Invincibility); 
	
	if (ZhonyaSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ZhonyaSound, GetActorLocation());
	}
	
	if (OverlayMaterial)
		Character->GetMesh()->SetOverlayMaterial(OverlayMaterial);
	
	Mesh->SetVisibility(false); 
	bActivated = true; 
	
	// 3. Set up Timer 
	TWeakObjectPtr<AAssignment_08Character> WeakChar = Character; 
	TWeakObjectPtr<AZhonya> WeakSelf = this;
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, 
		[WeakChar,WeakSelf]()
		{
			// Rollback Character 
			if (WeakChar.IsValid())
			{
				UCharacterMovementComponent* MovementComponent = WeakChar->GetCharacterMovement();
				if (MovementComponent)
				{
					MovementComponent->SetMovementMode(MOVE_Walking);
				}
				
				WeakChar->GetMesh()->bNoSkeletonUpdate = false;
				WeakChar->SetCurrentPlayerState(ECharacterstatus::Idle);
				WeakChar->GetMesh()->SetOverlayMaterial(nullptr);
			}
			
			// Destroy Actor
			if (WeakSelf.IsValid())
			{
				WeakSelf->DestroyItem(); 
			}
			
		},
		Duration,
		false
	);
	
}

