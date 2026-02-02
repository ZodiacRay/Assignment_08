// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterStateTextWidget.h"
#include "Components/TextBlock.h"

UCharacterStateTextWidget::UCharacterStateTextWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void UCharacterStateTextWidget::UpdateTextBlock(FText InText)
{
	TextBlock->SetText(InText); 
}
