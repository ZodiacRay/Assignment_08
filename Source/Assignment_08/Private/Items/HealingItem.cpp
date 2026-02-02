// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealingItem.h"
#include "Assignment_08Character.h"

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	// 1. Check Character 
	AAssignment_08Character* Character = Cast<AAssignment_08Character>(Activator);
	if (Character == nullptr) return ; 
	
	
	// 2. Heal Logic
	Character->AddHealth(HealAmount);
	bActivated = true; 
	Mesh->SetVisibility(false);
	
	Character->UpdateStateWidget(FText::FromString("++"));
	 
	// 3. Destroy Logic
	TWeakObjectPtr<AHealingItem> WeakSelf = this; 
	TWeakObjectPtr<AAssignment_08Character> WeakChar = Cast<AAssignment_08Character>(Character); 
	GetWorldTimerManager().SetTimer(
		ItemTimer, [WeakChar, WeakSelf]()
		{
			WeakChar->ClearStateWidget();
			WeakSelf->DestroyItem(); 
		}, 
		1.f,
		false
	); 
}

