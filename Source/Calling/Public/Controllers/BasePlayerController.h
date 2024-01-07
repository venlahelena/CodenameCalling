// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IInteractionInterface;

UCLASS()
class CALLING_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ABasePlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	float TraceDistance = 1000.0f;

private:

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	void Move(const struct FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);

	void PlayerCameraTrace();
	IInteractionInterface* LastActor;
	IInteractionInterface* ThisActor;


	
};
