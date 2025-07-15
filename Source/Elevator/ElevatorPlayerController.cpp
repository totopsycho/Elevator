// Copyright Epic Games, Inc. All Rights Reserved.


#include "ElevatorPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ElevatorCameraManager.h"

AElevatorPlayerController::AElevatorPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AElevatorCameraManager::StaticClass();
}

void AElevatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
