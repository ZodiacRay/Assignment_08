// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "JumpPad.generated.h"


UCLASS()
class ASSIGNMENT_08_API AJumpPad : public ABaseItem
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	virtual void ActivateItem(AActor* Activator) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float MeshScale = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float LaunchPower = 1000.f; 
};
