// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseInventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class CALLING_API ABaseInventoryItem : public ABaseItem
{
	GENERATED_BODY()


public:
	ABaseInventoryItem();

protected:

    virtual void HandleInventoryItemInteraction() override;
	
};
