// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Core/Interfaces/LaserInterface.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/ProjectileInterface.h"
#include "PhysicsCube.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCubeDestroyedSignature);

UCLASS()
class ELEVATOR_API APhysicsCube : public AActor, public ILaserInterface, public IProjectileInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsCube();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstanceDynamic* CubeMatInst;

	UPROPERTY(BlueprintAssignable)
	FOnCubeDestroyedSignature OnCubeDestroy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PhysicsCubeMesh;

	virtual void OnActorEnterLaser_Implementation();
	
	//Timeline Begin (Timeline comp declared on public )

	UPROPERTY()
	FTimeline MatInstTimelineComp;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* MatInstCurve;

	UFUNCTION()
	void OnMatInsTimelineUpdated(float alpha);

	UFUNCTION()
	void OnMastIntTimelineFinished();
	//End Timeline

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
