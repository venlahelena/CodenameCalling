// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}