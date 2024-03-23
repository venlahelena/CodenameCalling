// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Puzzle/BasePuzzleItem.h"
#include "Controllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Cameras/BaseCameraActor.h"
#include "Characters/PlayerCharacter.h"

ABasePuzzleItem::ABasePuzzleItem()
{
}

void ABasePuzzleItem::HandlePuzzleInteraction()
{
    Super::HandlePuzzleInteraction();
    UE_LOG(LogTemp, Warning, TEXT("Rotating puzzle item interaction logic goes here!"));
    // Add code for camera zooming, rotation, etc.
  
    SpawnPuzzleCameraActor();
    NotifyCollectedForQuest();
}

void ABasePuzzleItem::SpawnPuzzleCameraActor()
{
    ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    if (BasePlayerController)
    {
        // Disable player input
        BasePlayerController->SetIgnoreMoveInput(true);
        BasePlayerController->SetIgnoreLookInput(true);
        BasePlayerController->SetShowMouseCursor(true);

        ABaseCameraActor* PuzzleCamera = GetWorld()->SpawnActor<ABaseCameraActor>(
            PuzzleCameraActorClass,
            GetActorLocation() + PuzzleCameraSpawnLocationOffset,
            GetActorRotation() + PuzzleCameraSpawnRotationOffset
        );

        if (PuzzleCamera && !bIsInspecting)
        {
            UE_LOG(LogTemp, Warning, TEXT("Spawned Camera Location: %s"), *PuzzleCamera->GetActorLocation().ToString());
            UE_LOG(LogTemp, Warning, TEXT("Spawned Camera Rotation: %s"), *PuzzleCamera->GetActorRotation().ToString());

            BasePlayerController->SetViewTargetWithBlend(PuzzleCamera, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
            bIsInspecting = true;

            UE_LOG(LogTemp, Warning, TEXT("bIsInspecting after setting to true: %s"), bIsInspecting ? TEXT("True") : TEXT("False"));
        }
    }
}

void ABasePuzzleItem::ReturnToOriginalCamera()
{
    if (bIsInspecting)
    {
        UE_LOG(LogTemp, Warning, TEXT("Return to original view"));
        UE_LOG(LogTemp, Warning, TEXT("bIsInspecting after setting to true: %s"), bIsInspecting ? TEXT("True") : TEXT("False"));

        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

        if (PlayerCharacter)
        {
            // Switch back to the original camera
            PlayerCharacter->SwitchToOriginalCamera();

            // Enable player input
            ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
            if (BasePlayerController)
            {
                BasePlayerController->SetIgnoreMoveInput(false);
                BasePlayerController->SetIgnoreLookInput(false);
                BasePlayerController->SetShowMouseCursor(false);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is nullptr during ReturnToOriginalCamera"));
        }

        bIsInspecting = false;
    }
}



void ABasePuzzleItem::DestroyPuzzleCameraActor()
{
}
