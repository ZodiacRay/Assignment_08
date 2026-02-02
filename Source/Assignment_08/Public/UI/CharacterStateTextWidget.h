// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStateTextWidget.generated.h"

class UTextBlock; 

UCLASS()
class ASSIGNMENT_08_API UCharacterStateTextWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UCharacterStateTextWidget(const FObjectInitializer& ObjectInitializer);
	
	void UpdateTextBlock(FText InText);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State Text", meta = (BindWidget))
	UTextBlock* TextBlock;
};
