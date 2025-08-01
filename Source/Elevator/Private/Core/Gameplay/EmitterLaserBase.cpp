// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/EmitterLaserBase.h"

// Sets default values
AEmitterLaserBase::AEmitterLaserBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Comp");

	EmitterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Emitter Mesh");
	EmitterMesh->SetupAttachment(RootComponent);

	ViewCylinder = CreateDefaultSubobject<UStaticMeshComponent>("View Cylinder");
	ViewCylinder->SetupAttachment(EmitterMesh);
}

// Called when the game starts or when spawned
void AEmitterLaserBase::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEmitterLaserBase::SphereTrace, 0.1f, true);
	
}

void AEmitterLaserBase::SphereTrace()
{
	UE_LOG(LogTemp, Log, TEXT("Timer"))
	
}

// Called every frame
void AEmitterLaserBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

