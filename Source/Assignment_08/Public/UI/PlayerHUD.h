// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"


class UStatBarWidget; 

UCLASS()
class ASSIGNMENT_08_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); 
	
	void NativeConstruct() override;

	void OnHealthChanged(float Value);
	
	void UpdateTimeBar(float Value, FText Text); 
	
protected: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta =(BindWidget))
	UStatBarWidget* HealthBar;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta =(BindWidget))
	UStatBarWidget* TimeBar;
};
