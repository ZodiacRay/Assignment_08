// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h" 

UStatBarWidget::UStatBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UStatBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpdateVisual(); 
}

void UStatBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UStatBarWidget::SetRatio(float Ratio)
{
	if (StatBar == nullptr) return; 
	
	StatBar->SetPercent(Ratio);
}

void UStatBarWidget::UpdateVisual()
{
	if (StatBar)
		StatBar->SetFillColorAndOpacity(BarColor); 
	
	if (StatText)
		StatText->SetText(TextContent); 
}
