// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BondageItem.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT_08_API ABondageItem : public ABaseItem
{
	GENERATED_BODY()
	
protected:
	
	
	
public:
	virtual void ActivateItem(AActor* Activator) override; 
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Duration = 2.f; 
	
};
