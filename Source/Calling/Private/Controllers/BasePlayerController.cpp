// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BasePlayerController.h"
#include "InputMappingContext.h"
#include "DrawDebugHelpers.h"
#include "Interface/InteractionInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();

    check(PlayerContext);

    UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(SubSystem);
    SubSystem->AddMappingContext(PlayerContext, 0);
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

        // Debug: Draw a debug line to visualize the trace
        DrawDebugLine(GetWorld(), CameraLocation, HitResult.ImpactPoint, FColor::Green, false, 1.0f, 0, 1.0f);

        UE_LOG(LogTemp, Warning, TEXT("Successful hit! Actor: %s"), *HitResult.GetActor()->GetName());
    }
}
