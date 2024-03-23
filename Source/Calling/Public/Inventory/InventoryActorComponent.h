#pragma once

#include "CoreMinimal.h"
#include "Structures/ItemStruct.h"
#include "Components/ActorComponent.h"
#include "InventoryActorComponent.generated.h"

struct FItemdata;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CALLING_API UInventoryActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryActorComponent();

	void AddItem(const FItemData& ItemData);

	void GetInventoryData(TMap<FString, FItemData>& InventoryData) const;


protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FString> ItemNames;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FItemData> ItemData;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	TArray<FItemData> Inventory;
		
};
