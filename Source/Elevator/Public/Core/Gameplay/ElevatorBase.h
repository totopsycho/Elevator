// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorBase.generated.h"

UCLASS()
class ELEVATOR_API AElevatorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorBase();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_LiftMove();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ElevatorMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
