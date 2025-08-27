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
	// Sets default values for this actor's properties
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

	/** Timeline component */
	FTimeline MyTimeline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* SceneComp;

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

	//Timeline Begin
	
	/** Curve asset pour piloter la timeline (à assigner dans l’éditeur ou par code) */
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FloatCurve;

	/** Callback Update */
	UFUNCTION()
	void TimelineUpdate(float Value);

	/** Callback Finished */
	UFUNCTION()
	void TimelineFinished();


	

};
