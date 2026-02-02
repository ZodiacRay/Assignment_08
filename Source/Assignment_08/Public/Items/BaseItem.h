// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ItemInterface.h"
#include "BaseItem.generated.h"

class USphereComponent; 
UCLASS()
class ASSIGNMENT_08_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void DestroyItem();
	
#pragma region Interface Functions 
protected:
	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override; 
	
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) override; 
	
	virtual void ActivateItem(AActor* Activator) override; 
	virtual FName GetItemType() const override; 
#pragma endregion 

protected:
	FTimerHandle ItemTimer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* Collision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bActivated = false;
};
