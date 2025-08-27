// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Projectile/ElevatorProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AElevatorProjectileBase::AElevatorProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RootComponent = SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereCollision->SetSphereRadius(20.f);
	SphereCollision->OnComponentHit.AddDynamic(this, &AElevatorProjectileBase::OnProjectileHit);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(" Projectile Mesh");
	ProjectileMesh->SetupAttachment(SphereCollision);
	ProjectileMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Comp");
	ProjectileMovementComp->InitialSpeed= 3000.f;
	ProjectileMovementComp->MaxSpeed = 3000.f;
	ProjectileMovementComp->bShouldBounce = true;
	


}

void AElevatorProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		float XImpactNormal = UKismetMathLibrary::Abs(Hit.ImpactNormal.X);
		if (UKismetMathLibrary::NearlyEqual_FloatFloat(XImpactNormal, 1.f, 0.2f))
		{
			OtherComp->SetConstraintMode(EDOFMode::XZPlane);
			OtherComp->AddImpulse(FVector(FMath::Sign(GetVelocity().X) * ImpulseFactor, 0.f, 0.f), NAME_None, true );
			return;
		}
		OtherComp->SetConstraintMode(EDOFMode::YZPlane);
		OtherComp->AddImpulse(FVector(0.f, FMath::Sign(GetVelocity().Y)* ImpulseFactor, 0.f), NAME_None, true);
	}
	Destroy();
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

