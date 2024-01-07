// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "BaseItem.generated.h"

class UStaticMeshComponent;

UCLASS()
class CALLING_API ABaseItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ItemMeshComponent;

public:

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

};
