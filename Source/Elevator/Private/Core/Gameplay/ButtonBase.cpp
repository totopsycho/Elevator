// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/ButtonBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AButtonBase::AButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CacheButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cache Button Mesh");

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	ButtonMesh->SetupAttachment(CacheButtonMesh);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	TriggerBox->SetupAttachment(ButtonMesh);

}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

