
#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Controllers/BasePlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/HUD/BaseHUD.h"
#include "Controllers/BasePlayerController.h"
#include "Inventory/InventoryActorComponent.h"
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

    OriginalCamera = CameraComponent;

    InventoryComponent = CreateDefaultSubobject<UInventoryActorComponent>(TEXT("InventoryComponent"));
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

void APlayerCharacter::SwitchToOriginalCamera()
{
    if (OriginalCamera)
    {
        ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetController());
        if (PlayerController)
        {
            UE_LOG(LogTemp, Warning, TEXT("Switching back to original camera"));

            PlayerController->SetViewTargetWithBlend(this, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
            PlayerController->SetShowMouseCursor(false);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("PlayerController is nullptr during camera switch"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("OriginalCamera is nullptr during camera switch"));
    }
}