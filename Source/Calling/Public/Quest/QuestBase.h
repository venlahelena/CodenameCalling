#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestBase.generated.h"

class ABaseEnemyCharacter;
class ABaseItem;

UENUM(BlueprintType)
enum class EQuestReward : uint8
{
    Default     UMETA(DisplayName = "Default"),
    Experience  UMETA(DisplayName = "Experience"),
    Currency    UMETA(DisplayName = "Currency")
};

UENUM(BlueprintType)
enum class EQuestClearCondition : uint8
{
    Default     UMETA(DisplayName = "Default"),
    Kill        UMETA(DisplayName = "Kill"),
    Collect     UMETA(DisplayName = "Collect"),
    Destination UMETA(DisplayName = "Destination")
};

USTRUCT(BlueprintType)
struct FQuestReward
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestReward RewardType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ABaseItem> Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Experience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Currency;
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestClearCondition ClearingType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ABaseEnemyCharacter> EnemyToSlay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ABaseItem> ItemToCollect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ObjectiveDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ObjectiveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int NumberRequired;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCompleted;
};

UCLASS(BlueprintType)
class CALLING_API UQuestBase : public UObject
{
    GENERATED_BODY()

    UQuestBase();

public:

    UFUNCTION(BlueprintCallable)
    void SetQuestDetails(FString Name, FString Description);

    UFUNCTION(BlueprintCallable)
    void SetQuestObjectives(int ObjectiveNumber, TSubclassOf<ABaseEnemyCharacter> Enemy, TSubclassOf<ABaseItem> Item, FString DescriptionOne, FString DescriptionTwo, int NumberRequired);

    UFUNCTION(BlueprintCallable)
    void SetNumberOfObjectives(int NumberObjectives);

    UFUNCTION()
    void UpdateQuest();

    UFUNCTION(BlueprintCallable)
    void UpdateObjectives(int NumberObjectives, int UpdateValue);

    UFUNCTION(BlueprintCallable)
    void UpdateObjectiveDescription(FString& Description, int NumberRequired);

    UFUNCTION(BlueprintCallable)
    void FinishObjective(int NumberObjectives);

    UFUNCTION()
    void FinishQuest();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FQuestReward Reward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestObjective> QuestObjectives;
};
