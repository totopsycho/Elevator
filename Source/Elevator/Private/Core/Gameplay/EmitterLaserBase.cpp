// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/EmitterLaserBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include <ShooterCharacter.h>
#include "Kismet/KismetMathLibrary.h"

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

void AEmitterLaserBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	EmitterMesh->SetWorldScale3D(FVector(EmitterScale, EmitterScale, 1.f));
	ViewCylinder->SetWorldScale3D(FVector(4.f, EmitterScale, EmitterScale));

	UMaterialInstanceDynamic* EmitterMatInst = EmitterMesh->CreateDynamicMaterialInstance(0);
	UMaterialInstanceDynamic* ViewCylinderMatInst = ViewCylinder->CreateDynamicMaterialInstance(0);
	if (LaserType == ELaserType::TeleportLaser)
	{
		
		EmitterMatInst->SetScalarParameterValue(FName("SwitchColor"), 0.f);

		ViewCylinderMatInst->SetScalarParameterValue(FName("CylinderState"), 0.f);
	}

	if (LaserType == ELaserType::DeadLaser)
	{
		
		EmitterMatInst->SetScalarParameterValue(FName("SwitchColor"), 1.f);

		ViewCylinderMatInst->SetScalarParameterValue(FName("CylinderState"), 1.f);
	}

	

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
	FVector Start = EmitterMesh->GetComponentLocation();
	FVector UpVectorMultiplied = EmitterMesh->GetUpVector() * TraceMaxDistance;
	FVector End = Start + UpVectorMultiplied;
	float Radius = EmitterScale * 50.f;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult OutHit;
	
	bool bIsHit =UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		ActorsToIgnore, EDrawDebugTrace::ForOneFrame,OutHit, true );

	if (bIsHit)
	{
		AActor* HitActor = OutHit.GetActor();
		FVector ImpactPoint = OutHit.ImpactPoint;
		FVector TraceStart = OutHit.TraceStart;

		if (HitActor->Implements<ULaserInterface>())
		{
			if (LaserType == ELaserType::DeadLaser)
			{
				ILaserInterface::Execute_OnActorEnterLaser(HitActor);
				return;
			}

			if (LaserType == ELaserType::TeleportLaser)
			{
				FVector WorldTeleportLocation = UKismetMathLibrary::TransformLocation(GetActorTransform(), TeleportLocation);
				HitActor->SetActorLocation(WorldTeleportLocation);
				return;
			}
			
		}

		float VectorLength = UKismetMathLibrary::VSize(TraceStart - ImpactPoint) * 0.002f;

		FVector ViewCylinderScale = ViewCylinder->GetComponentScale();

		ViewCylinder->SetWorldScale3D(FVector(VectorLength, ViewCylinderScale.Y, ViewCylinderScale.Z));
		
	}



}

// Called every frame
void AEmitterLaserBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

