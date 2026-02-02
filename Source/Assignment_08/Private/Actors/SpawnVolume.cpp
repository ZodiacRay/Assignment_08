// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"


ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SetRootComponent(SpawningBox);
	
	SpawningBox->SetHiddenInGame(true);
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (bShouldLoop)
	{
		// Spawn Timer 
		GetWorld()->GetTimerManager().SetTimer(
			SpawnTimer,
			this,
			&ThisClass::SpawnRandomItem,
			SpawnTime,
			true 
		);
	}
	else
	{
		for (int32 i = 0; i < SpawnCount; i++)
		{
			SpawnRandomItem();
		}
	}
	
	
}

void ASpawnVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
	
	Super::EndPlay(EndPlayReason);
}

#pragma region Spawn 
void ASpawnVolume::SpawnRandomItem()
{
	if ( FItemSpawnRow* SelectedRow = GetRandomItem() )
	{
		SpawnItemFromRow(*SelectedRow); 
	}
}

void ASpawnVolume::SpawnItemFromRow(const FItemSpawnRow& Row)
{
	if (UClass* ActualClass = Row.ItemClass.Get())
	{
		FTransform SpawnTransform; 
		SpawnTransform.SetScale3D(GetRandomScale(Row));
		SpawnTransform.SetLocation(GetRandomPointInVolume());
		
		if (bShouldRandomRoation)
		{
			SpawnTransform.SetRotation(GetRandomRotation().Quaternion());
		}	
		else
		{
			SpawnTransform.SetRotation(FQuat::Identity);
		}
		
		
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			Row.ItemClass, SpawnTransform
		); 
	}
}

#pragma endregion

#pragma region Get Random Values 

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();
	
	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		GetActorLocation().Z
	);
}

FRotator ASpawnVolume::GetRandomRotation() const
{
	return FRotator(
		FMath::FRandRange(-180.f, 180.f),
		FMath::FRandRange(-180.f, 180.f),
		FMath::FRandRange(-180.f, 180.f)
	);
}

FVector ASpawnVolume::GetRandomScale(const FItemSpawnRow& Row)
{
	if (Row.ItemClass == nullptr) return FVector(1.f);
	
	float RandVal = FMath::FRandRange(Row.ItemMinScale, Row.ItemMaxScale);
	
	if (FMath::IsNearlyZero(RandVal)) return FVector(1.f);
	
	return FVector(RandVal);
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!SpawnTable) return nullptr;
	
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	SpawnTable->GetAllRows(ContextString, AllRows); 
	
	if (AllRows.IsEmpty()) return nullptr;
	
	float TotalChance = 0.f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}
	
	const float RandValue = FMath::RandRange(0.f, TotalChance);
	float AccumulateChance = 0.f;
	
	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (AccumulateChance > RandValue)
		{
			return Row;
		}
	}
	
	return nullptr;
	
}

#pragma endregion