// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Projectile/ElevatorProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AElevatorProjectileBase::AElevatorProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(" Projectile Mesh");
	ProjectileMesh->SetupAttachment(SphereCollision);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Comp");
	


}

// Called when the game starts or when spawned
void AElevatorProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevatorProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

