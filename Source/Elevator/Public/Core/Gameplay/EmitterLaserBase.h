// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h" 
#include "EmitterLaserBase.generated.h"


UENUM(BlueprintType)
enum class ELaserType : uint8
{
	TeleportLaser,
	DeadLaser
};

USTRUCT(BlueprintType)
struct FLaserInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly)
	float TraceMaxDistance = 1000.f;

	UPROPERTY(EditInstanceOnly, meta = (ClampMin = "1.0", ClampMax = "4.0"))
	float EmitterScale = 1.f;

	UPROPERTY(EditInstanceOnly)
	ELaserType LaserType;

	UPROPERTY(EditInstanceOnly, meta = (MakeEditWidget = true))
	FVector TeleportLocation;

};

UCLASS()
class ELEVATOR_API AEmitterLaserBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEmitterLaserBase();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EmitterMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ViewCylinder;

	UFUNCTION()
	void SphereTrace();

	UPROPERTY(EditInstanceOnly, Category = "Laser Info")
	FLaserInfo LaserInfo;


};
