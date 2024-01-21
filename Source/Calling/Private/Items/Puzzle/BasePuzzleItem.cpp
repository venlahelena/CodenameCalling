// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Puzzle/BasePuzzleItem.h"
#include "Controllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Cameras/BaseCameraActor.h"

ABasePuzzleItem::ABasePuzzleItem()
{
}

void ABasePuzzleItem::HandlePuzzleInteraction()
{
    Super::HandlePuzzleInteraction();
    UE_LOG(LogTemp, Warning, TEXT("Rotating puzzle item interaction logic goes here!"));
    // Add code for camera zooming, rotation, etc.
    SpawnPuzzleCameraActor();

}

void ABasePuzzleItem::SpawnPuzzleCameraActor()
{
    ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    if (BasePlayerController)
    {
        TogglePlayerInput(false);

        ABaseCameraActor* PuzzleCamera = GetWorld()->SpawnActor<ABaseCameraActor>(
            PuzzleCameraActorClass,
            GetActorLocation() + PuzzleCameraSpawnLocationOffset,
            GetActorRotation() + PuzzleCameraSpawnRotationOffset
        );

        if (PuzzleCamera)
        {
            UE_LOG(LogTemp, Warning, TEXT("Spawned Camera Location: %s"), *PuzzleCamera->GetActorLocation().ToString());
            UE_LOG(LogTemp, Warning, TEXT("Spawned Camera Rotation: %s"), *PuzzleCamera->GetActorRotation().ToString());

            BasePlayerController->SetViewTargetWithBlend(PuzzleCamera, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
        }
    }
}

void ABasePuzzleItem::DestroyPuzzleCameraActor()
{
}

void ABasePuzzleItem::TogglePlayerInput(bool bEnableInput)
{
    ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    if (PlayerController)
    {
        PlayerController->SetShowMouseCursor(true);

        PlayerController->SetIgnoreMoveInput(!bEnableInput);
        PlayerController->SetIgnoreLookInput(!bEnableInput);
    }
}
