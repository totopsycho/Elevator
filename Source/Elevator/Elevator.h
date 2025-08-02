// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//SpherTraceByChannel
/*FVector Start = EmitterMesh->GetComponentLocation();
FVector UpVectorMultiplied = EmitterMesh->GetUpVector() * TraceMaxDistance;
FVector End = Start + UpVectorMultiplied;
float Radius = EmitterScale * 50.f;
TArray<AActor*> ActorsToIgnore;
ActorsToIgnore.Add(this);
FHitResult OutHit;

bool bIsHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
	ActorsToIgnore, EDrawDebugTrace::ForOneFrame, OutHit, true);

if (bIsHit)
{
	AActor* HitActor = OutHit.GetActor();
	UE_LOG(LogTemp, Warning, TEXT("Actor Name is %s"), *HitActor->GetName())
}*/
