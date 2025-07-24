// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/ElevatorBase.h"

// Sets default values
AElevatorBase::AElevatorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Comp");

	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Elevator Mesh");
	ElevatorMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AElevatorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevatorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

