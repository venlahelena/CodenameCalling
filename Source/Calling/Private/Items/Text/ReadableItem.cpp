// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Text/ReadableItem.h"

AReadableItem::AReadableItem()
{
}

void AReadableItem::HandleReadableTextInteraction()
{
    Super::HandleReadableTextInteraction();

    UE_LOG(LogTemp, Warning, TEXT("Interacted in the readable chilld!"));
    if (WidgetClass)
    {
        WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

        if (WidgetInstance)
        {
            WidgetInstance->AddToViewport();
        }
    }
}
