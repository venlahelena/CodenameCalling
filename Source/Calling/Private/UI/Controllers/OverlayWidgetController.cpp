// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controllers/OverlayWidgetController.h"
#include "AbilitySystem/BaseAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBaseAttributeSet* BaseAttributeSet = CastChecked<UBaseAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(BaseAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BaseAttributeSet->GetMaxHealth());
	OnPowerChanged.Broadcast(BaseAttributeSet->GetPower());
	OnMaxPowerChanged.Broadcast(BaseAttributeSet->GetMaxPower());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBaseAttributeSet* BaseAttributeSet = CastChecked<UBaseAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetPowerAttribute()).AddUObject(this, &UOverlayWidgetController::PowerChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetMaxPowerAttribute()).AddUObject(this, &UOverlayWidgetController::MaxPowerChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::PowerChanged(const FOnAttributeChangeData& Data) const
{
	OnPowerChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxPowerChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxPowerChanged.Broadcast(Data.NewValue);
}
