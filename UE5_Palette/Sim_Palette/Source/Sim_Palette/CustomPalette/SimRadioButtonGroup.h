// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// engine
#include <CoreMinimal.h>
#include <Components/CanvasPanel.h>

// project
#include "SimRadioButtonGroup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimRadioButtonGroupStateChanged, const int32, ActiveIndex, const USimRadioButton*, ActiveWidget);

class USimRadioButton;
class USimCheckBox;
/**
 * 
 */
UCLASS()
class SIM_PALETTE_API USimRadioButtonGroup : public UCanvasPanel
{
	GENERATED_BODY()

protected:
	virtual void PostLoad() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	bool IsCheckState(int32 InRadioButtonIndex, ECheckBoxState InCheckState);
	int32 GetActiveIndex() { return ActiveIndex; }

	void SetActiveIndex(int32 InIndex) { ActiveIndex = InIndex; }
	void SetRadioButtonCheck(int32 InIndex, bool InBroadcast = false);
	void SetRadioButtons();
	void ResetRadioButtons();

	void AddRadioButton(TObjectPtr<USimRadioButton> InRadioButton);
	void RemoveRadioButton(TObjectPtr<USimRadioButton> InRadioButton);

private:
	int32 ActiveIndex = -1;

public:
	FOnSimRadioButtonGroupStateChanged OnRadioButtonGroupStateChanged;

	UFUNCTION()
	virtual void OnCheckBoxStateChanged(const USimCheckBox* InCheckBox, const bool InIsChecked);

	UPROPERTY(EditAnywhere, Category = "Sim")
	TArray<TObjectPtr<USimRadioButton>> RadioButtonList;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};
