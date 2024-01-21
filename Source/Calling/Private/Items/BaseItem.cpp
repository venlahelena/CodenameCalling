// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMeshComponent;

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItem::HighlightActor()
{
	ItemMeshComponent->SetRenderCustomDepth(true);
	ItemMeshComponent->SetCustomDepthStencilValue(255.0f);
}

void ABaseItem::UnHighlightActor()
{
	ItemMeshComponent->SetRenderCustomDepth(false);
}

void ABaseItem::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact function called!"));

    switch (ItemType)
    {
    case EItemType::PuzzleItem:
        HandlePuzzleInteraction();
        break;

    case EItemType::ReadableText:
        HandleReadableTextInteraction();
        break;

    case EItemType::InventoryItem:
        HandleInventoryItemInteraction();
        break;
    default:
        UE_LOG(LogTemp, Error, TEXT("Unhandled item type in Interact function!"));
        break;
    }
}

void ABaseItem::HandlePuzzleInteraction()
{
    // Add specific logic for puzzle item interactions here
    UE_LOG(LogTemp, Warning, TEXT("Puzzle item interaction logic goes here!"));
}

void ABaseItem::HandleReadableTextInteraction()
{
    // Add specific logic for readable text interactions here
    UE_LOG(LogTemp, Warning, TEXT("Readable text interaction logic goes here!"));
}

void ABaseItem::HandleInventoryItemInteraction()
{
    // Add specific logic for inventory item interactions here
    UE_LOG(LogTemp, Warning, TEXT("Inventory item interaction logic goes here!"));
}
