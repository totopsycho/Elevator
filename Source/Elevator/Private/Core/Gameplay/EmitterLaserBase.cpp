// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/EmitterLaserBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include <ShooterCharacter.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/KismetMathLibrary.h"


AEmitterLaserBase::AEmitterLaserBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;

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
	ViewCylinder->SetWorldScale3D(FVector(EmitterHeight, EmitterScale, EmitterScale));

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

void AEmitterLaserBase::BeginPlay()
{
	Super::BeginPlay();

	if (bShouldShowNiagaraTeleportLocation && AuraSystem && LaserType == ELaserType::TeleportLaser)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AuraSystem,
			UKismetMathLibrary::TransformLocation(GetActorTransform(), TeleportLocation),
			FRotator(0.f, 0.f, 0.f),
			FVector(1.f, 1.f, 1.f));
	}

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

	
	if (bIsHit )
	{
		AActor* HitActor = OutHit.GetActor();
		FVector ImpactPoint = OutHit.ImpactPoint;
		FVector TraceStart = OutHit.TraceStart;
		UPrimitiveComponent* HitComponent = OutHit.GetComponent();

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
				HitComponent->SetConstraintMode(EDOFMode::None);
				HitActor->SetActorLocation(WorldTeleportLocation, false, nullptr, ETeleportType::TeleportPhysics);
				if (HitActor->GetVelocity().X > 10.f || HitActor->GetVelocity().X < -10.f)
				{
					HitComponent->SetConstraintMode(EDOFMode::XZPlane);
				}
				else if (HitActor->GetVelocity().Y > 10.f || HitActor->GetVelocity().Y < -10.f)
				{
					HitComponent->SetConstraintMode(EDOFMode::YZPlane);
				}
				
				return;
			}
			
		}

		float VectorLength = UKismetMathLibrary::VSize(TraceStart - ImpactPoint) * 0.002f;

		ViewCylinder->SetWorldScale3D(FVector(VectorLength, EmitterScale, EmitterScale));

		return;
		
	}

	ViewCylinder->SetWorldScale3D(FVector(EmitterHeight, EmitterScale, EmitterScale));

}



