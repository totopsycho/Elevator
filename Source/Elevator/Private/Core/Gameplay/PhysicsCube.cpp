// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/PhysicsCube.h"

// Sets default values
APhysicsCube::APhysicsCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = PhysicsCubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("PhysicCubeMesh");
	PhysicsCubeMesh->SetSimulatePhysics(true);
}

void APhysicsCube::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CubeMatInst = PhysicsCubeMesh->CreateDynamicMaterialInstance(0);
}

// Called when the game starts or when spawned
void APhysicsCube::BeginPlay()
{
	Super::BeginPlay();

	if (MatInstCurve)
	{
		FOnTimelineFloat UpdateFunction{};
		UpdateFunction.BindUFunction(this, FName("OnMatInsTimelineUpdated"));

		FOnTimelineEvent FinishedFunction{};
		FinishedFunction.BindUFunction(this, FName("OnMastIntTimelineFinished"));

		// Setup de la timeline
		MatInstTimelineComp.AddInterpFloat(MatInstCurve, UpdateFunction);
		MatInstTimelineComp.SetTimelineFinishedFunc(FinishedFunction);

		MatInstTimelineComp.SetLooping(false);   // Pas en boucle
	}
	PhysicsCubeMesh->SetConstraintMode(EDOFMode::XZPlane);
	
}

void APhysicsCube::OnMatInsTimelineUpdated(float alpha)
{

	CubeMatInst->SetScalarParameterValue(FName("Dissolve"), alpha);
}

void APhysicsCube::OnMastIntTimelineFinished()
{
	Destroy();
}

// Called every frame
void APhysicsCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MatInstTimelineComp.TickTimeline(DeltaTime);
}

void APhysicsCube::OnActorEnterLaser_Implementation()
{
	PhysicsCubeMesh->SetSimulatePhysics(false);
	PhysicsCubeMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	MatInstTimelineComp.PlayFromStart();
	OnCubeDestroy.Broadcast();
}

