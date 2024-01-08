// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BaseHUD.h"
#include "UI/Widgets/BaseWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	UBaseWidget* Widget = CreateWidget<UBaseWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();

}
