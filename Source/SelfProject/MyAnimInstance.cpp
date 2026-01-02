// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		MyPlayer = Cast<AMyPlayer>(Pawn);

		if (IsValid(MyPlayer))
		{
			CharacterMovement = MyPlayer->GetCharacterMovement();
		}
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(CharacterMovement))
	{
		FVector Velocity = CharacterMovement->Velocity;
		float GroundSpeed = Velocity.Size2D();

		FRotator Rotation = MyPlayer->GetActorRotation();
		FVector UnrotateVector = Rotation.UnrotateVector(Velocity);
		Vertical = UnrotateVector.X;
		Horizontal = UnrotateVector.Y;

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();
		ShouldMove = GroundSpeed > 0.1 && Acceleration != FVector::Zero();

		
	}
}