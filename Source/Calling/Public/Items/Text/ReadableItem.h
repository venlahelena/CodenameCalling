// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Blueprint/UserWidget.h"
#include "ReadableItem.generated.h"

class UUserWidget;


UCLASS()
class CALLING_API AReadableItem : public ABaseItem
{
	GENERATED_BODY()

public:
    AReadableItem();

protected:

    UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget> WidgetClass;

    TObjectPtr<UUserWidget> WidgetInstance;

    virtual void HandleReadableTextInteraction() override;
	
};
