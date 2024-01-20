// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BasePlayerController.h"
#include "InputMappingContext.h"
#include "DrawDebugHelpers.h"
#include "Interface/InteractionInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Items/InspectableItem.h"

ABasePlayerController::ABasePlayerController()
{
    OriginalCameraArmLength = 200.0f;
    InspectableItem = nullptr;
}

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();

    check(PlayerContext);

    UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (SubSystem)
    {
        SubSystem->AddMappingContext(PlayerContext, 0);
    }
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    PlayerCameraTrace();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Look);
}

void ABasePlayerController::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABasePlayerController::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABasePlayerController::ZoomIn()
{
    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (CameraManager)
    {
        ACharacter* ControlledCharacter = GetCharacter();
        if (ControlledCharacter)
        {
            USpringArmComponent* SpringArm = ControlledCharacter->FindComponentByClass<USpringArmComponent>();

            if (SpringArm)
            {
                OriginalCameraArmLength = SpringArm->TargetArmLength;
                SpringArm->TargetArmLength = OriginalCameraArmLength * 0.5f; // Adjust the zoom factor as needed
            }
        }
    }
}

void ABasePlayerController::ZoomOut()
{
    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (CameraManager)
    {
        ACharacter* ControlledCharacter = GetCharacter();
        if (ControlledCharacter)
        {
            USpringArmComponent* SpringArm = ControlledCharacter->FindComponentByClass<USpringArmComponent>();

            if (SpringArm)
            {
                SpringArm->TargetArmLength = OriginalCameraArmLength;
            }
        }
    }
}

void ABasePlayerController::PlayerCameraTrace()
{
    // Get the location and rotation of the player's camera
    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerCameraManager->GetCameraViewPoint(CameraLocation, CameraRotation);

    // Calculate the end position of the trace
    FVector TraceEnd = CameraLocation + CameraRotation.Vector() * TraceDistance;

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetPawn());

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, CollisionParams);

    if (bHit)
    {
        LastActor = ThisActor;
        ThisActor = Cast<IInteractionInterface>(HitResult.GetActor());

        if (LastActor == nullptr)
        {
            if (ThisActor != nullptr)
            {
                ThisActor->HighlightActor();
            }

        }
        else
        {
            if (ThisActor == nullptr)
            {
                LastActor->UnHighlightActor();
            }
            else
            {
                if (LastActor != ThisActor)
                {
                    LastActor->UnHighlightActor();
                    ThisActor->HighlightActor();
                }
            }

        }

        if (InspectableItem)
        {
            ZoomIn();
        }

        UE_LOG(LogTemp, Warning, TEXT("Successful hit! Actor: %s"), *HitResult.GetActor()->GetName());
    }
}
