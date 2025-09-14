// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/CubeSpawner.h"
#include "NiagaraComponent.h"




ACubeSpawner::ACubeSpawner()
{
 
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>("Scene Comp");
	SetRootComponent(SceneComp);

	CubeSpawnerSystem = CreateDefaultSubobject<UNiagaraComponent>("Cube Spawner System");
	CubeSpawnerSystem->SetupAttachment(SceneComp);

	
	
}


void ACubeSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}


