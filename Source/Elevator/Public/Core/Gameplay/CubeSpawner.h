// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeSpawner.generated.h"

class UNiagaraComponent;
class APhysicsCube;

UCLASS()
class ELEVATOR_API ACubeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APhysicsCube> PhysicsCubeClass;

	APhysicsCube* SpawnedCube;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UNiagaraComponent* CubeSpawnerSystem;

	UFUNCTION()
	void SpawnCube();

	UFUNCTION()
	void OnCubeDestroyed();

};
