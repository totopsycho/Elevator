// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonBase.generated.h"

class UBoxComponent;
class AElevatorBase;

UCLASS()
class ELEVATOR_API AButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonBase();

	UFUNCTION()
	void OnComponentOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	
	UPROPERTY(EditInstanceOnly)
	TArray<AElevatorBase*> ElevatorReferences;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CacheButtonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ButtonMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Button")
	FVector InitialButtonLocation;

	UFUNCTION()
	void OnProjeticleStartTriggering();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Button")
	FVector BackButtonLocation;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ResetButtonPosition();

	UFUNCTION(BlueprintCallable)
	void OnTimelineUpdateButton(float alpha);

	UFUNCTION(BlueprintCallable)
	void OnTimelineFinished();
	

	UPROPERTY()
	bool IsButtonActivated = false;

	UPROPERTY()
	float ButtonPlayRate;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
