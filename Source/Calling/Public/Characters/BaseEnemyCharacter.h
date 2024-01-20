// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CALLING_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ABaseEnemyCharacter();

protected:

	virtual void BeginPlay() override;
	
};
