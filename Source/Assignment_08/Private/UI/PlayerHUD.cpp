// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"
#include "Assignment_08Character.h"
#include "UI/StatBarWidget.h"

UPlayerHUD::UPlayerHUD(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (APawn* OwningPawn = GetOwningPlayerPawn())
	{
		if (AAssignment_08Character* Player = Cast<AAssignment_08Character>(OwningPawn))
		{
			Player->OnHealthChanged.AddUObject(this, &ThisClass::OnHealthChanged); 
			Player->BroadcastHealthChanged(); 
			
			HealthBar->TextContent = FText::FromString("HP"); 
		}
	}
}

void UPlayerHUD::OnHealthChanged(float Value)
{
	HealthBar->UpdateVisual(); 
	
	HealthBar->SetRatio(Value);
}

void UPlayerHUD::UpdateTimeBar(float Value, FText Text)
{
	TimeBar->TextContent = Text;
	TimeBar->SetRatio(Value);
	
	TimeBar->UpdateVisual();
}


