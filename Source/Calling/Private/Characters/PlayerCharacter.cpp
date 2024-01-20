// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Controllers/BasePlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/HUD/BaseHUD.h"
#include "Controllers/BasePlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 350.0f, 0.0f);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 200.0f;
    SpringArmComponent->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->SetRelativeLocation(FVector(100.0f, 20.0f, 55.0f));
    CameraComponent->bUsePawnControlRotation = true;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{

    ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>();
    check(BasePlayerState);

    BasePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BasePlayerState, this);
    AbilitySystemComponent = BasePlayerState->GetAbilitySystemComponent();
    AttributeSet = BasePlayerState->GetAttributeSet();

    if (ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController()))
    {
        if (ABaseHUD* BaseHUD = Cast<ABaseHUD>(BasePlayerController->GetHUD()))
        {
            BaseHUD->InitOverlay(BasePlayerController, BasePlayerState, AbilitySystemComponent, AttributeSet);
        }
    }
}
