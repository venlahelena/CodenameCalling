// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "Structures/ItemStruct.h"
#include "BaseItem.generated.h"

class UStaticMeshComponent;

struct FItemData;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Default,
	PuzzleItem,
	ReadableText,
	InventoryItem,
};

UCLASS()
class CALLING_API ABaseItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	EItemType ItemType;

	FItemData GeItemData() const { return ItemData; };

protected:
	virtual void BeginPlay() override;

	bool bIsInspecting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ItemMeshComponent;

public:

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual void Interact() override;
	virtual void StopInspect() override;

	virtual void HandlePuzzleInteraction();
	virtual void HandleReadableTextInteraction();
	virtual void HandleInventoryItemInteraction();

};
