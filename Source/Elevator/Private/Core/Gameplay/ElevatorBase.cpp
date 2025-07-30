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

float AElevatorBase::GetElevatorPlayRate()
{
	//Stocker les distances dans un tableau
	TArray<float> Distances;
	Distances.Add(UKismetMathLibrary::Abs(XDistance));
	Distances.Add(UKismetMathLibrary::Abs(YDistance));
	Distances.Add(UKismetMathLibrary::Abs(ZDistance));

	//Trouver la valeur maximum dans le tableau

	int32 Index = 0;
	float MaxValue = 0.f;
	UKismetMathLibrary::MaxOfFloatArray(Distances, Index, MaxValue);

	// Déterminer le playrate de l'elevator

	return	ElevatorPlayRate = ElevatorSpeed / MaxValue;
	
}

// Called when the game starts or when spawned
void AElevatorBase::BeginPlay()
{
	Super::BeginPlay();

	GetElevatorPlayRate();
	

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

