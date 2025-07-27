// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/ElevatorBase.h"
#include "Kismet/KismetMathLibrary.h"

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

	InitialLocation = ElevatorMesh->GetRelativeLocation();

	ALocation = InitialLocation;
	BLocation = FVector(InitialLocation.X + XDistance, InitialLocation.Y + YDistance, InitialLocation.Z + ZDistance);

	
}

void AElevatorBase::OnLiftTimelineUpdated(float alpha)
{
	if (Direction)
	{
		FVector LerpAB = UKismetMathLibrary::VLerp(ALocation, BLocation, alpha);
		ElevatorMesh->SetRelativeLocation(LerpAB);
	}
	else
	{
		FVector LerpBA = UKismetMathLibrary::VLerp(BLocation, ALocation, alpha);
		ElevatorMesh->SetRelativeLocation(LerpBA);
	}
}

void AElevatorBase::OnLiftTimelineFinished()
{
	if (Direction)
	{
		Direction = false;
		return;
	}

	Direction = true;
}

// Called every frame
void AElevatorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

