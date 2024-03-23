// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Inventory/BaseInventoryItem.h"
#include "Characters/PlayerCharacter.h"
#include "Controllers/BasePlayerController.h"
#include "Inventory/InventoryActorComponent.h"

ABaseInventoryItem::ABaseInventoryItem()
{
}

void ABaseInventoryItem::HandleInventoryItemInteraction()
{
	Super::HandleInventoryItemInteraction();

    ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetCharacter());
    UInventoryActorComponent* InventoryComponent = PlayerCharacter->InventoryComponent;

    if (InventoryComponent)
    {

        InventoryComponent->AddItem(this->GeItemData());
    }

	NotifyCollectedForQuest();
}
