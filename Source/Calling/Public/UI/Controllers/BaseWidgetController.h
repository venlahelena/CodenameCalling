// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseWidgetController.generated.h"


//class UAttributeSet;
//class UAbilitySystemComponent;


UCLASS()
class CALLING_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	//UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	//TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	//TObjectPtr<UAttributeSet> AttributeSet;
	
};