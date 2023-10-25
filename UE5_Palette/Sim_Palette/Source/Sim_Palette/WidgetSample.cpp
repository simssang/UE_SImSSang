// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSample.h"
#include "CustomPalette/SimRadioButtonGroup.h"

void UWidgetSample::NativeConstruct()
{
	Super::NativeConstruct();

	if (nullptr != SimRadioButtonGroup)
	{
		SimRadioButtonGroup->SetRadioButtons();
	}
}

void UWidgetSample::NativeDestruct()
{
	Super::NativeDestruct();
}