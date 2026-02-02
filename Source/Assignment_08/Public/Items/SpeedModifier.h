// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "SpeedModifier.generated.h"


class UCharacterMovementComponent;

UCLASS()
class ASSIGNMENT_08_API ASpeedModifier : public ABaseItem
{
	GENERATED_BODY()
	
public:
	virtual void ActivateItem(AActor* Activator) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ModifierRate = 1.f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Duration = 1.f; 
	
	float SpeedModifyAmount; 
	
	FVector ScaleModifyAmount; 
};
