// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BondageItem.h"
#include "Assignment_08Character.h"
#include "GameFramework/CharacterMovementComponent.h"



void ABondageItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	if (GetWorld()->GetTimerManager().IsTimerActive(ItemTimer)) return;
	
	AAssignment_08Character* Character = Cast<AAssignment_08Character>(Activator);
	if (Character == nullptr) return; 

	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	if (MovementComponent == nullptr) return; 
	
	MovementComponent->SetMovementMode(MOVE_None); 
	bActivated = true; 
	Mesh->SetVisibility(false); 
	
	Character->UpdateStateWidget(FText::FromString("Can't Move")); 
	
	TWeakObjectPtr<AAssignment_08Character> WeakChar = Character;
	GetWorld()->GetTimerManager().SetTimer(
		ItemTimer,
		[WeakChar, this]()
		{
			if (WeakChar.IsValid())
			{
				WeakChar->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
				
				WeakChar->ClearStateWidget(); 
			}
			DestroyItem(); 
		},
		Duration,
		false
	);
	
	
	
}


