// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// engine
#include <CoreMinimal.h>

// project
#include "SimCheckBox.h"

// generated
#include <SimRadioButton.generated.h>

/**
 * 
 */
UCLASS()
class SIM_PALETTE_API USimRadioButton : public USimCheckBox
{
	GENERATED_BODY()
	
public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};
