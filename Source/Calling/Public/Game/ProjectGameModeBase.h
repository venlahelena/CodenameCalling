// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectGameModeBase.generated.h"

class ABaseHUD;

UCLASS()
class CALLING_API AProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AProjectGameModeBase();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateObjective(int ObjectiveNumber);

	UFUNCTION(BlueprintImplementableEvent)
	void HideObjective(int ObjectiveNumber);

	UFUNCTION(BlueprintImplementableEvent)
	void HideQuest();

};
