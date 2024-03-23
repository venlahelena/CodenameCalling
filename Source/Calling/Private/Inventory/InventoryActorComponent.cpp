// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryActorComponent.h"

// Sets default values for this component's properties
UInventoryActorComponent::UInventoryActorComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}

void UInventoryActorComponent::AddItem(const FItemData& NewItemData)
{
    bool bItemAdded = false;

    for (FItemData& InventoryItem : Inventory)
    {
        if (InventoryItem.ItemID == NewItemData.ItemID)
        {
            InventoryItem.CurrentStackAmount += NewItemData.CurrentStackAmount;

            InventoryItem.CurrentStackAmount = FMath::Min(InventoryItem.CurrentStackAmount, InventoryItem.MaximumStackAmount);

            bItemAdded = true;

            UE_LOG(LogTemp, Warning, TEXT("Added %d %s to inventory. New stack amount: %d"), NewItemData.CurrentStackAmount, *NewItemData.ItemName, InventoryItem.CurrentStackAmount);

            break;
        }
    }

    if (!bItemAdded)
    {
        Inventory.Add(NewItemData);

        UE_LOG(LogTemp, Warning, TEXT("Added new item %s to inventory."), *NewItemData.ItemName);
    }
}


void UInventoryActorComponent::GetInventoryData(TMap<FString, FItemData>& InventoryData) const
{
    for (const FItemData& Item : Inventory)
    {
        InventoryData.Add(Item.ItemName, Item);
    }
}


void UInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInventoryActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

