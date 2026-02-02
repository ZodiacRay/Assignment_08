// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	// 어떤 아이템 클래스를 스폰할지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
	// 이 아이템의 스폰 확률
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemMinScale = 1.f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemMaxScale = 1.f; 
};
