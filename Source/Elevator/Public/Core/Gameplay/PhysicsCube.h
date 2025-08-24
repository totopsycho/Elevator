// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/LaserInterface.h"
#include "GameFramework/Actor.h"
#include "PhysicsCube.generated.h"

UCLASS()
class ELEVATOR_API APhysicsCube : public AActor, public ILaserInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PhysicsCubeMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
