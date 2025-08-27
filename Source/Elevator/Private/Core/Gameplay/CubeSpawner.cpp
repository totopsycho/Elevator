// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/CubeSpawner.h"
#include "NiagaraComponent.h"
#include "Core/Gameplay/PhysicsCube.h"
#include "NiagaraSystem.h"

// Sets default values
ACubeSpawner::ACubeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Comp");

	CubeSpawnerSystem = CreateDefaultSubobject<UNiagaraComponent>("Cube Spawn VFX");
	CubeSpawnerSystem->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACubeSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnCube();
}

// Called every frame
void ACubeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeSpawner::SpawnCube()
{
	FVector SpawnLocation = CubeSpawnerSystem->GetComponentLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	SpawnedCube = GetWorld()->SpawnActor<APhysicsCube>(PhysicsCubeClass, SpawnTransform, SpawnParams);

	if (SpawnedCube)
	{
		SpawnedCube->OnCubeDestroy.AddDynamic(this, &ThisClass::OnCubeDestroyed);
	}
}

void ACubeSpawner::OnCubeDestroyed()
{
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, this, &ACubeSpawner::SpawnCube, 2.f, false
	);
}

