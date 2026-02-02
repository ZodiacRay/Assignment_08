// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "HealingItem.generated.h"

UCLASS()
class ASSIGNMENT_08_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	virtual void ActivateItem(AActor* Activator) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float HealAmount = 30.f;
};
