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
