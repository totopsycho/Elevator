// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/ElevatorBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AElevatorBase::AElevatorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Comp");

	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Elevator Mesh");
	ElevatorMesh->SetupAttachment(RootComponent);


}

void AElevatorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update la timeline à chaque frame
	MyTimeline.TickTimeline(DeltaTime);
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

	// D�terminer le play rate de l'elevator

	return	ElevatorPlayRate = ElevatorSpeed / MaxValue;
	
}

// Called when the game starts or when spawned
void AElevatorBase::BeginPlay()
{
	Super::BeginPlay();

	if (FloatCurve)
	{
		// Bind des fonctions
		FOnTimelineFloat UpdateFunction{};
		UpdateFunction.BindUFunction(this, FName("TimelineUpdate"));

		FOnTimelineEvent FinishedFunction{};
		FinishedFunction.BindUFunction(this, FName("TimelineFinished"));

		// Setup de la timeline
		MyTimeline.AddInterpFloat(FloatCurve, UpdateFunction);
		MyTimeline.SetTimelineFinishedFunc(FinishedFunction);

		MyTimeline.SetLooping(false);   // Pas en boucle
	}

	GetElevatorPlayRate();
	

	InitialLocation = ElevatorMesh->GetRelativeLocation();

	ALocation = InitialLocation;
	BLocation = FVector(InitialLocation.X + XDistance, InitialLocation.Y + YDistance, InitialLocation.Z + ZDistance);

	
}

void AElevatorBase::OnLiftTimelineUpdated(float alpha)
{

	
	
}

void AElevatorBase::OnLiftTimelineFinished()
{
	
}

void AElevatorBase::TimelineUpdate(float Value)
{
	if (Direction)
	{
		FVector LerpAB = UKismetMathLibrary::VLerp(ALocation, BLocation, Value);
		ElevatorMesh->SetRelativeLocation(LerpAB);
	}
	else
	{
		FVector LerpBA = UKismetMathLibrary::VLerp(BLocation, ALocation, Value);
		ElevatorMesh->SetRelativeLocation(LerpBA);
	}
}

void AElevatorBase::TimelineFinished()
{
	if (Direction)
	{
		Direction = false;
	}
	else
	{
		Direction = true;
	}
	
	FHitResult Hit = BoxTraceForPhysicsCube();
	if (Hit.bBlockingHit)
	{
		AActor* HitActor = Hit.GetActor();
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (!HitActor ->IsA(APawn::StaticClass()))
		{
			HitComp->SetSimulatePhysics(true);
			HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
	}
}

FHitResult AElevatorBase::BoxTraceForPhysicsCube()
{
	FVector Start = ElevatorMesh->GetComponentLocation();
	FVector End = FVector(Start.X, Start.Y, Start.Z + 100.f);
	FVector BoxExtent = FVector::ZeroVector;
	FVector Origin = FVector::ZeroVector;
	float SphereRadius = 0.f;
	UKismetSystemLibrary::GetComponentBounds(ElevatorMesh, Origin, BoxExtent,SphereRadius);
	TArray<AActor*> ActorsToIgnore;
	FHitResult OutHit;
	ActorsToIgnore.Add(this);
	FVector HalfSize = BoxExtent - FVector(15.f, 15.f, 0.f);
	
	bool bIsHit =UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, End, HalfSize, FRotator(0.f, 0.f, 0.f), UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
	ActorsToIgnore, EDrawDebugTrace::None,OutHit, true );
	if (!bIsHit)
	{
		return FHitResult();
	}
	return OutHit;
}



