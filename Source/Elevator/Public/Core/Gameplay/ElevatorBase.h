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

	UPROPERTY()
	bool Direction = true;

	UPROPERTY()
	FVector InitialLocation;

	UPROPERTY()
	FVector ALocation;

	UPROPERTY()
	FVector BLocation;

	UFUNCTION(BlueprintCallable)
	void OnLiftTimelineUpdated(float alpha);

	UFUNCTION(BlueprintCallable)
	void OnLiftTimelineFinished();

	UPROPERTY(EditInstanceOnly, Category = "Elevator Movement")
	float XDistance;

	UPROPERTY(EditInstanceOnly, Category = "Elevator Movement")
	float YDistance;
	
	UPROPERTY(EditInstanceOnly, Category = "Elevator Movement")
	float ZDistance;

	UPROPERTY(EditInstanceOnly, Category = "Elevator Movement")
	float ElevatorSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Elevator Movement")
	float ElevatorPlayRate;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
