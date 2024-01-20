// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "GameplayTagsModule.h"
#include "GameplayTagContainer.h"
#include "InspectableItem.generated.h"

/**
 * 
 */
UCLASS()
class CALLING_API AInspectableItem : public ABaseItem
{
	GENERATED_BODY()

public:

    AInspectableItem();

    UPROPERTY(EditAnywhere, Category = "Gameplay Tags")
    FGameplayTagContainer ItemTags;
	
};
