// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSample.generated.h"

class USimRadioButtonGroup;
/**
 * 
 */
UCLASS()
class SIM_PALETTE_API UWidgetSample : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USimRadioButtonGroup> SimRadioButtonGroup;
};
