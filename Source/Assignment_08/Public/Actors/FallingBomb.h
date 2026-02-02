// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingBomb.generated.h"

class USphereComponent;
class UProjectileMovementComponent; 
class UArrowComponent;
class UStaticMeshComponent;
class UParticleSystem; 
class UMaterialInterface; 

UCLASS()
class ASSIGNMENT_08_API AFallingBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void DrawWarningDecal(); 

	UFUNCTION() 
	void OnMyProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity); 
	
	virtual void Destroyed() override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Mesh; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<USphereComponent> SphereCollision; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UArrowComponent> Arrow;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UProjectileMovementComponent>  ProjectileMovement;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom")
	float MovementSpeed = 1000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom")
	float GravityScale = 4.f; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
	float DamageAmount = 10.f; 
	
#pragma region Materials
	UPROPERTY(EditAnywhere, Category = "WarningDecal")
	UMaterialInterface* WarningDecalMaterial;
	
	UPROPERTY() 
	UDecalComponent* SpawnedDecal; 
	
	UPROPERTY(EditAnywhere, Category = "WarningDecal")
	float DecalLifeSpan = 2.0f; 
	
	UPROPERTY(EditAnywhere, Category = "WarningDecal")
	float DecalDepth = 200.f; 
	
#pragma endregion
	
#pragma region Effects 
protected:
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ParticleToSpawn;
    
	UPROPERTY(EditAnywhere, Category = "Effects")
	FVector ParticleScale = FVector(1.0f);
    
   	UPROPERTY(EditAnywhere, Category = "Effects")
   	float TraceRadius = 100.f;
   
   	UPROPERTY(EditAnywhere, Category = "Effects")
   	bool bShowDebugTrace = false; 

#pragma endregion	
};
