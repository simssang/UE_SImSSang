// Fill out your copyright notice in the Description page of Project Settings.


#include "SimRadioButton.h"

#define LOCTEXT_NAMESPACE "UMG"

#if WITH_EDITOR
const FText USimRadioButton::GetPaletteCategory()
{
	return LOCTEXT("", "SimPalette");
}
#endif

#undef  LOCTEXT_NAMESPACE