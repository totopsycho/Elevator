// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/ElevatorCube.h"

// Sets default values
AElevatorCube::AElevatorCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElevatorCubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Elevator Cube Mesh");
	ElevatorCubeMesh->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AElevatorCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevatorCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

