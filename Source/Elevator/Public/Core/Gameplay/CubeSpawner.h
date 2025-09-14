// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeSpawner.generated.h"

class UNiagaraComponent;

UCLASS()
class ELEVATOR_API ACubeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	ACubeSpawner();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* CubeSpawnerSystem;



};
