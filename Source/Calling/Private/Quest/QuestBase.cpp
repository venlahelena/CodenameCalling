// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestBase.h"
#include "Game/ProjectGameModeBase.h"
#include "Characters/BaseEnemyCharacter.h"
#include "Items/BaseItem.h"

UQuestBase::UQuestBase()
{
	QuestName = "Default quest name";
	QuestDescription = "Default Quest description";

	Reward.RewardType = EQuestReward::Default;
	Reward.Experience = 2.0f;
	Reward.Currency = 2;
	Reward.Item = nullptr;
}


void UQuestBase::SetQuestDetails(FString Name, FString Description)
{
    QuestName = Name;
    QuestDescription = Description;

    UE_LOG(LogTemp, Warning, TEXT("Quest details set: %s - %s"), *QuestName, *QuestDescription);
}

void UQuestBase::SetQuestObjectives(int ObjectiveNumber, TSubclassOf<ABaseEnemyCharacter> Enemy, TSubclassOf<ABaseItem> Item, FString DescriptionOne, FString DescriptionTwo, int NumberRequired)
{
    if (ObjectiveNumber < QuestObjectives.Num())
    {
        QuestObjectives[ObjectiveNumber].ClearingType = EQuestClearCondition::Kill;
        QuestObjectives[ObjectiveNumber].EnemyToSlay = Enemy;

    }
    else if (Item != nullptr)
    {
        QuestObjectives[ObjectiveNumber].ClearingType = EQuestClearCondition::Collect;
        QuestObjectives[ObjectiveNumber].ItemToCollect = Item;
    }

    QuestObjectives[ObjectiveNumber].ObjectiveID = ObjectiveNumber;
    QuestObjectives[ObjectiveNumber].NumberRequired = NumberRequired;

    QuestObjectives[ObjectiveNumber].ObjectiveDescription.Append(DescriptionOne + "<NR>");
    QuestObjectives[ObjectiveNumber].ObjectiveDescription.AppendInt(NumberRequired);
    QuestObjectives[ObjectiveNumber].ObjectiveDescription.Append("<NR>" + DescriptionTwo);

    UE_LOG(LogTemp, Warning, TEXT("Objective %d description set: %s"), ObjectiveNumber, *QuestObjectives[ObjectiveNumber].ObjectiveDescription);
}

void UQuestBase::SetNumberOfObjectives(int NumberObjectives)
{
    QuestObjectives.SetNum(NumberObjectives);
    UE_LOG(LogTemp, Warning, TEXT("Number of objectives set to: %d"), NumberObjectives);
}

void UQuestBase::UpdateQuest()
{
    UE_LOG(LogTemp, Warning, TEXT("Quest updated"));
}

void UQuestBase::UpdateObjectives(int NumberObjectives, int UpdateValue)
{
    if (NumberObjectives < QuestObjectives.Num())
    {
        QuestObjectives[NumberObjectives].NumberRequired -= UpdateValue;

        UpdateObjectiveDescription(QuestObjectives[NumberObjectives].ObjectiveDescription, QuestObjectives[NumberObjectives].NumberRequired);

        if (auto ProjectGameModeBase = Cast<AProjectGameModeBase>(GetOuter()))
        {
            ProjectGameModeBase->UpdateObjective(NumberObjectives);
        }

        UE_LOG(LogTemp, Warning, TEXT("Objective %d updated. Remaining: %d"), NumberObjectives, QuestObjectives[NumberObjectives].NumberRequired);

        if (QuestObjectives[NumberObjectives].NumberRequired <= 0)
        {
            FinishObjective(NumberObjectives);
        }
    }
}

void UQuestBase::UpdateObjectiveDescription(FString& Description, int NumberRequired)
{
    FString FirstString;
    FString SecondString;
    FString UpdatedNumber;

    UpdatedNumber.AppendInt(NumberRequired);

    Description.Split("<NR>", &FirstString, &SecondString);
    SecondString = SecondString.Replace(*SecondString.Left(SecondString.Find("<NR>")), *UpdatedNumber);
    Description = FirstString.Append("<NR>").Append(SecondString);

}

void UQuestBase::FinishObjective(int NumberObjectives)
{
    if (NumberObjectives < QuestObjectives.Num())
    {
        QuestObjectives[NumberObjectives].bIsCompleted = true;

        if (auto ProjectGameModeBase = Cast<AProjectGameModeBase>(GetOuter()))
        {
            ProjectGameModeBase->HideObjective(NumberObjectives);
        }

        int numberFinished = 0;

        for (int i = 0; i < QuestObjectives.Num(); ++i)
        {
            if (QuestObjectives[i].bIsCompleted)
            {
                ++numberFinished;
            }
        }

        if (numberFinished >= QuestObjectives.Num())
        {
            FinishQuest();
        }
    }
}

void UQuestBase::FinishQuest()
{
    UE_LOG(LogTemp, Warning, TEXT("Quest finished"), *QuestName);

    if (auto ProjectGameModeBase = Cast<AProjectGameModeBase>(GetOuter()))
    {
        ProjectGameModeBase->HideQuest();
    }

}

