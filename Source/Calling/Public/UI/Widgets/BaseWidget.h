// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class CALLING_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemsAdded(const TMap<FString, FItemData>& Inventory);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowAllItemsInInventory(const TMap<FString, FItemData>& InventoryData);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
