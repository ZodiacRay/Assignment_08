// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FallingBomb.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/DecalComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Assignment_08Character.h"



AFallingBomb::AFallingBomb()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);	
	SphereCollision->SetSphereRadius(25.f);
	SphereCollision->SetNotifyRigidBodyCollision(true);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetCollisionProfileName(TEXT("BlockAll"));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereCollision); 
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow")); 
	Arrow->SetupAttachment(SphereCollision);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->bShouldBounce = true; 
}


void AFallingBomb::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovement->OnProjectileBounce.AddDynamic(this,&ThisClass::OnMyProjectileBounce); 
	
	FVector Scale = GetActorScale3D();
	float Modifier = (Scale.X + Scale.Y + Scale.Z) / 3; 
	
	DamageAmount *= Modifier;
	TraceRadius *= Modifier;
	ParticleScale *= Modifier;
	
	DrawWarningDecal(); 
	
}


void AFallingBomb::DrawWarningDecal()
{
	FPredictProjectilePathParams PathParams;
	PathParams.StartLocation = GetActorLocation();            
	PathParams.LaunchVelocity = ProjectileMovement->Velocity;
	
	if(PathParams.LaunchVelocity.IsNearlyZero())
	{
		PathParams.LaunchVelocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
	}
	
	PathParams.bTraceWithCollision = true;                     
	PathParams.ProjectileRadius = SphereCollision->GetUnscaledSphereRadius();
	PathParams.MaxSimTime = 5.f;                                
	PathParams.bTraceWithChannel = true;
	PathParams.TraceChannel = ECC_Visibility;                   
	PathParams.ActorsToIgnore.Add(this);
	PathParams.OverrideGravityZ = GetWorld()->GetGravityZ() * ProjectileMovement->ProjectileGravityScale;
	
	FPredictProjectilePathResult PathResult;
	
	bool bHit = UGameplayStatics::PredictProjectilePath(GetWorld(), PathParams, PathResult);
	
	if (bHit && WarningDecalMaterial)
	{
		FVector DecalSize = FVector(DecalDepth, TraceRadius, TraceRadius);
		
		SpawnedDecal = UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(),
			WarningDecalMaterial,
			DecalSize, 
			PathResult.HitResult.Location,           
			PathResult.HitResult.ImpactNormal.Rotation()         
		);
	}
		
}

void AFallingBomb::OnMyProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	// Ignore same class 
	if (ImpactResult.GetActor() == this) return;
	
	// Remove Decal  
	if(SpawnedDecal)
	{
		SpawnedDecal->DestroyComponent(); 
	}
	
	// Trace For Damage 
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this); 
	ActorsToIgnore.Add(GetOwner()); 
	TArray<FHitResult> SphereHits;

	bool bHit = UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(),
		ImpactResult.Location, 
		ImpactResult.Location + FVector(0, 0, 1.f), 
		TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn), 
		false,
		ActorsToIgnore,
		bShowDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		SphereHits,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		2.0f
	);

	// Spawn Effect  
	if (ParticleToSpawn)
	{
		UParticleSystemComponent* NiagaraComp = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ParticleToSpawn,
			ImpactResult.Location,
			ImpactResult.ImpactNormal.Rotation(),
			ParticleScale,
			true 
		);
	}

	if (bHit)
	{
		for (FHitResult& HitResult : SphereHits )
		{
			if (AAssignment_08Character* Character = Cast<AAssignment_08Character>(HitResult.GetActor()))
			{
				UGameplayStatics::ApplyDamage(
				Character, 
				DamageAmount, 
				nullptr,
				this, 
				UDamageType::StaticClass()
				);
				
			}
		}
	}
	
	Destroy();
}

void AFallingBomb::Destroyed()
{
	Super::Destroyed();
	
	if (SpawnedDecal)
	{
		SpawnedDecal->DestroyComponent();
	}
}


