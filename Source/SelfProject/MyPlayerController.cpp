// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Character.h"
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJumping);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyPlayerController::OnAttack);
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

void AMyPlayerController::OnAttack()
{
	if (AMyPlayer* myPlayer = Cast<AMyPlayer>(GetPawn()))
	{
		myPlayer->Attack();
	}
}

#pragma region Jump

void AMyPlayerController::Jump()
{
	if (ACharacter* controlledPawn = Cast<ACharacter>(GetPawn()))
	{
		controlledPawn->Jump();
	}
}

void AMyPlayerController::StopJumping()
{
	if (ACharacter* controlledPawn = Cast<ACharacter>(GetPawn()))
	{
		controlledPawn->StopJumping();
	}
}

#pragma endregion

