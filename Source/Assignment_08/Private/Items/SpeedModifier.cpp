// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SpeedModifier.h"
#include "Assignment_08Character.h"

void ASpeedModifier::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	if (bActivated == true) return; 
	
	// 1. Check Character 
	AAssignment_08Character* Character = Cast<AAssignment_08Character>(Activator);
	if (Character == nullptr) return;
	
	// 2. Item Logic 
	Character->AddSpeedMultiplier(ModifierRate - 1.f); 
	
	FVector OriginalScale = Character->GetActorScale3D();
 	
	float TargetRatio = 1.f / ModifierRate;
	TargetRatio = FMath::Clamp(TargetRatio, 0.25f, 8.f);
	
	FVector TargetScale = OriginalScale * TargetRatio;
	
	ScaleModifyAmount = TargetScale - OriginalScale; 
	Character->SetActorScale3D(TargetScale);
	
	bActivated = true; 
	Mesh->SetVisibility(false); 
	
	FText UIText = ModifierRate > 1 ? FText::FromString("Speed Up") : FText::FromString("Slowed");
	Character->UpdateStateWidget(UIText); 
	
	// 3.Set up Timer 
	TWeakObjectPtr<AAssignment_08Character> WeakChar = Cast<AAssignment_08Character>(Character);
	TWeakObjectPtr<ASpeedModifier> WeakSelf = Cast<ASpeedModifier>(this);
	GetWorld()->GetTimerManager().SetTimer(
		ItemTimer,
		[WeakChar, WeakSelf]()
		{
			// Rollback Character 
			if (WeakChar.IsValid())
			{
				WeakChar->RemoveSpeedMultiplier(WeakSelf->ModifierRate - 1.f);
				WeakChar->SetActorScale3D(WeakChar->GetActorScale3D() - WeakSelf->ScaleModifyAmount); 
				WeakChar->ClearStateWidget(); 
			}
			
			// Destory Actor 
			if (WeakSelf.IsValid())
			{
				WeakSelf->DestroyItem();
			}
			
		},
		Duration,
		false
	);
}



