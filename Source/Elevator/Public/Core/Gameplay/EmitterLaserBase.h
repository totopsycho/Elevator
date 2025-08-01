// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmitterLaserBase.generated.h"

UCLASS()
class ELEVATOR_API AEmitterLaserBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmitterLaserBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EmitterMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ViewCylinder;

	UFUNCTION()
	void SphereTrace();

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
