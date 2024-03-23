// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BasePuzzleItem.generated.h"

class ABasePlayerController;
class ABaseCameraActor;

UCLASS()
class CALLING_API ABasePuzzleItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ABasePuzzleItem();

	virtual void HandlePuzzleInteraction() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle Camera")
    FVector PuzzleCameraSpawnLocationOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle Camera")
    FRotator PuzzleCameraSpawnRotationOffset;

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Puzzle Camera")
    TSubclassOf<ABaseCameraActor> PuzzleCameraActorClass;

    UPROPERTY()
    TObjectPtr<ABaseCameraActor> PuzzleCameraActor;

    void SpawnPuzzleCameraActor();

    void ReturnToOriginalCamera();

    void DestroyPuzzleCameraActor();

};
