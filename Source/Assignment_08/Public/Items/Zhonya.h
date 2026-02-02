// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Zhonya.generated.h"

class USoundWave;
UCLASS()
class ASSIGNMENT_08_API AZhonya : public ABaseItem
{
	GENERATED_BODY()

public:
	virtual void ActivateItem(AActor* Activator) override; 

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UMaterialInterface* OverlayMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Duration = 2.f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USoundBase* ZhonyaSound; 
	
	FTimerHandle TimerHandle; 
};
