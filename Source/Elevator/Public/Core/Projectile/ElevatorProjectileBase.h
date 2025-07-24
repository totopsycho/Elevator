// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/ProjectileInterface.h"
#include "ElevatorProjectileBase.generated.h"


class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ELEVATOR_API AElevatorProjectileBase : public AActor, public IProjectileInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
