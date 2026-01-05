// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Game/ThirdPersons/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	FollowCamera->SetupAttachment(CameraBoom);
	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 150.0f), FRotator(-20.0f, 0.0f, 0.0f));
	CameraBoom->TargetArmLength = 400.f;

	static ConstructorHelpers::FClassFinder<UAnimInstance>AI(TEXT("/Script/Engine.AnimBlueprint'/Game/My/Anim/ABP_MyPlayer.ABP_MyPlayer_C'"));
	if (AI.Succeeded())
	{
		GetMesh()->SetAnimClass(AI.Class);
	}
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPlayer::Attack()
{
	FHitResult HitResult;
	FCollisionQueryParams Parms(NAME_None, false, this);

	float AttackRange = 200.f;
	float AttackRadius = 40.f;
	float AttackHalfHeight = 90.f;

	FVector StartPos = GetActorLocation();
	FVector EndPos = GetActorLocation() + GetActorForwardVector() * AttackRange;

	bool Result = GetWorld()->SweepSingleByChannel
	(
		OUT HitResult, 
		StartPos,
		EndPos,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeCapsule(AttackRadius, AttackHalfHeight),
		Parms
	);

	FQuat AttackRotation = FRotationMatrix::MakeFromZ(EndPos).ToQuat();
	FColor AttackColor = Result ? FColor::Green : FColor::Red;
	
	DrawDebugCapsule
	(
		GetWorld(),
		StartPos,
		AttackHalfHeight,
		AttackRadius,
		AttackRotation,
		AttackColor,
		false,
		2.0f
	);


	if (Result && HitResult.GetActor())
	{
		UE_LOG(LogTemp, Log, TEXT("Hit : %s"), *HitResult.GetActor()->GetName())
	}
}



