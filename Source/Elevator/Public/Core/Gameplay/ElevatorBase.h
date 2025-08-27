// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "ElevatorBase.generated.h"


UCLASS()
class ELEVATOR_API AElevatorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AElevatorBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_LiftMove();

	UFUNCTION()
	float GetElevatorPlayRate();

	UFUNCTION()
	FHitResult BoxTraceForPhysicsCube();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ElevatorMesh;
	
	UPROPERTY()
	FTimeline ElevatorTimeline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* SceneComp;

	//Begin Elevator Movement
	UPROPERTY()
	bool Direction = true;

	UPROPERTY()
	FVector InitialLocation;

	UPROPERTY()
	FVector ALocation;

	UPROPERTY()
	FVector BLocation;
	
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

	// End Elevator movement
	
	//Timeline Begin (Timeline comp declared on public )
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FloatCurve;

	UFUNCTION()
	void OnLiftTimelineUpdated(float alpha);

	UFUNCTION()
	void OnLiftTimelineFinished();
	//End Timeline
	


	

};
