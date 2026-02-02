// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ItemSpawnRow.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class ASSIGNMENT_08_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public: 
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	virtual void SpawnRandomItem() ;
	
	UFUNCTION(BlueprintCallable, Category="Spawn")
	void SpawnItemFromRow(const FItemSpawnRow& Row); 
	
public:	
	UFUNCTION(BlueprintCallable, Category="Spawn")
	FVector GetRandomPointInVolume() const;
	
	UFUNCTION(BlueprintCallable, Category="Spawn")
	FRotator GetRandomRotation() const;
	
	UFUNCTION(BlueprintCallable, Category="Spawn")
	FVector GetRandomScale(const FItemSpawnRow& Row); 
	
	FItemSpawnRow* GetRandomItem() const;
	
	UDataTable* GetSpawnTable() const { return SpawnTable; } 
protected:
	FTimerHandle SpawnTimer; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn")
	UBoxComponent* SpawningBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn")
	UDataTable* SpawnTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn")
	float SpawnTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn")
	bool bShouldLoop = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	float SpawnMinScale = 1.f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	float SpawnMaxScale = 1.8f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	bool bShouldRandomRoation = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	int32 SpawnCount = 1;
};
