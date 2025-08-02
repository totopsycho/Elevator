// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/EmitterLaserBase.h"
#include "Kismet/KismetSystemLibrary.h"

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
		UE_LOG(LogTemp, Warning, TEXT("Actor Name is %s"), *HitActor->GetName())
	}



}

// Called every frame
void AEmitterLaserBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

