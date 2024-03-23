// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/BaseWidget.h"

void UBaseWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

void UBaseWidget::ShowAllItemsInInventory(const TMap<FString, FItemData>& InventoryData)
{
	OnItemsAdded(InventoryData);
}
