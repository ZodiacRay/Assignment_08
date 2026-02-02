// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/SphereComponent.h"


ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bActivated = false; 
	Scene = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision =CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic")); 
	Collision->SetupAttachment(Scene);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnItemBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnItemEndOverlap);
}

void ABaseItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(ItemTimer);
	}
	
	Super::EndPlay(EndPlayReason);
}

void ABaseItem::DestroyItem()
{
	Destroy(); 
}

#pragma region Interface Functions 
void ABaseItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ActivateItem(OtherActor);
	}
}


void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ABaseItem::ActivateItem(AActor* Activator)
{
	if (bActivated == true|| GetWorld()->GetTimerManager().IsTimerActive(ItemTimer)) return ; 
	
}

FName ABaseItem::GetItemType() const
{
	return ItemType; 
}
#pragma endregion




