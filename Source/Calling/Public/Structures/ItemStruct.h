#pragma once

#include "ItemStruct.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Default,
	Consumable,
	Puzzle,
	Weapon,
};


USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaximumStackAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 CurrentStackAmount = 1;

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 ItemID;

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly, Category = "Item")
	EItemCategory ItemCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 RestorationAmount;
};
