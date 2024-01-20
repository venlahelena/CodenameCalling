// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InspectableItem.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AInspectableItem::AInspectableItem()
{
	// Add a default tag to the ItemTags container if needed
	ItemTags.AddTag(FGameplayTag::RequestGameplayTag("InspectableItem"));
}