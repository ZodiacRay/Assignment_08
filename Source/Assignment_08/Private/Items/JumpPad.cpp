// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/JumpPad.h"
#include "GameFramework/Character.h"



void AJumpPad::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->SetWorldScale3D(FVector(MeshScale)); 
	LaunchPower *= MeshScale; 
}

void AJumpPad::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	
	if (ACharacter* Character = Cast<ACharacter>(Activator))
	{
		Character->LaunchCharacter(FVector(0,0,LaunchPower), true, false);
		bActivated = true;
		
		DestroyItem(); 
	}
}


