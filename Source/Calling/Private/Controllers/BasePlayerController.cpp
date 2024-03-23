// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BasePlayerController.h"
#include "InputMappingContext.h"
#include "DrawDebugHelpers.h"
#include "Characters/PlayerCharacter.h"
#include "Interface/InteractionInterface.h"
#include "Inventory/InventoryActorComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/Widgets/BaseWidget.h"
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

    EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ABasePlayerController::Interact);

    EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Completed, this, &ABasePlayerController::ToggleInventory);
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

    if (GetWorld() && GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, CollisionParams))
    {
        DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Green, false, 0.1f, 0, 1.0f);
    }

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
    }

}

void ABasePlayerController::Interact()
{
    if (ThisActor)
    {
        ThisActor->Interact();
    }
    else
    {
        ThisActor = nullptr;
    }
}

bool ABasePlayerController::IsInventoryOpen() const
{
    return (InventoryWidgetInstance && InventoryWidgetInstance->IsVisible());
}

void ABasePlayerController::CloseInventory()
{
    UE_LOG(LogTemp, Warning, TEXT("Closing inventory"));

    InventoryWidgetInstance->RemoveFromParent();
    InventoryWidgetInstance = nullptr;

    SetShowMouseCursor(false);
    SetIgnoreMoveInput(false);
    SetIgnoreLookInput(false);

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
}

void ABasePlayerController::OpenInventory()
{
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

    if (!PlayerCharacter || !PlayerCharacter->InventoryComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Player Character or Inventory Component is not valid"));
        return;
    }

    TMap<FString, FItemData> InventoryData;
    PlayerCharacter->InventoryComponent->GetInventoryData(InventoryData);

    if (InventoryWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Creating and adding inventory widget"));

        InventoryWidgetInstance = CreateWidget<UUserWidget>(this, InventoryWidgetClass);
        if (!InventoryWidgetInstance)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create Inventory Widget"));
            return;
        }

        SetShowMouseCursor(true);
        SetIgnoreMoveInput(true);
        SetIgnoreLookInput(true);

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(InventoryWidgetInstance->TakeWidget());
        SetInputMode(InputMode);

        UBaseWidget* BaseWidget = Cast<UBaseWidget>(InventoryWidgetInstance);
        if (BaseWidget)
        {
            BaseWidget->OnItemsAdded(InventoryData);
        }

        InventoryWidgetInstance->AddToViewport();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Inventory Widget Class is not set"));
    }
}

void ABasePlayerController::ToggleInventory()
{
    if (IsInventoryOpen())
    {
        CloseInventory();
    }
    else
    {
        OpenInventory();
    }
}


