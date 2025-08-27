// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Projectile/ElevatorProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AElevatorProjectileBase::AElevatorProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RootComponent = SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereCollision->SetSphereRadius(20.f);
	SphereCollision->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileHit);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(" Projectile Mesh");
	ProjectileMesh->SetupAttachment(SphereCollision);
	ProjectileMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Comp");
	ProjectileMovementComp->InitialSpeed= 3000.f;
	ProjectileMovementComp->MaxSpeed = 3000.f;
	


}

void AElevatorProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Physic Actor"));
	}
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

