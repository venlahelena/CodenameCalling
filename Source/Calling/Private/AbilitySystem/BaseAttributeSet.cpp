// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAttributeSet.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitHealth(60.0f);
	InitMaxHealth(100.0f);
	InitPower(30.0f);
	InitMaxPower(50.0f);
}
