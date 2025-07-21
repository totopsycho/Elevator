// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Gameplay/ButtonBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AButtonBase::AButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CacheButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cache Button Mesh");

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	ButtonMesh->SetupAttachment(CacheButtonMesh);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	TriggerBox->SetupAttachment(ButtonMesh);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AButtonBase::OnComponentOverlapTrigger);

}

void AButtonBase::OnComponentOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Effectue la logique lorsqu'un élément chevauche mon trigger

	//1. Changer le matériel du button en rouge
	ButtonMesh->SetMaterial(0, ButtonMesh->GetMaterial(1));

	//2 . Le button part vers l'arrière
	InitialButtonLocation = ButtonMesh->GetRelativeLocation();
	ButtonMesh->SetRelativeLocation(FVector(InitialButtonLocation.X, InitialButtonLocation.Y,
		InitialButtonLocation.Z - 20.f));
	BackButtonLocation = ButtonMesh->GetRelativeLocation();

	//3. On envoie un événement au blueprint (pour la timeline)

	//4 . Le button va revenir à sa position initiale (VLerp)

	//5 . A la fin de la timeline, on revient à la couleur verte

	UE_LOG(LogTemp, Warning, TEXT("Overlap Detected"));
}

// Called when the game starts or when spawned
void AButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

