// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatBarWidget.generated.h"

class UProgressBar; 
class UTextBlock; 

UCLASS()
class ASSIGNMENT_08_API UStatBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UStatBarWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); 
	
	virtual void NativeConstruct() override;
	
	virtual void NativePreConstruct() override;
	
	void SetRatio(float Ratio);

public:
	void UpdateVisual();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="StatBar", meta=(BindWidget))
	TObjectPtr<UProgressBar> StatBar; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="StatBar", meta=(BindWidget))
	TObjectPtr<UTextBlock> StatText;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StatBar")
	FLinearColor BarColor = FLinearColor::Red; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StatBar")
	FText TextContent; 
};

