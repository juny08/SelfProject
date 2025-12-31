// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Pawn.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	APawn* controlledPawn = GetPawn();
	if (controlledPawn != nullptr)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		controlledPawn->AddMovementInput(controlledPawn->GetActorForwardVector(), MovementVector.Y);
		controlledPawn->AddMovementInput(controlledPawn->GetActorRightVector(), MovementVector.X);
	}
}
