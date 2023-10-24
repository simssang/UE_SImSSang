// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// engine
#include <CoreMinimal.h>

// project
#include "SimBaseCheckBox.h"
#include "SSimCheckBox.h"

// Generated
#include "SimCheckBox.generated.h"

UENUM()
enum class ESimCheckBoxState : uint8
{
	None,
	Normal,
	Hovered,
	Pressed,
	Disabled,
	SelectedNormal,
	SelectedHovered,
	SelectedPressed,

	Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSimCheckBoxStateChanged, const USimCheckBox*, CheckBox, const bool, IsChecked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimCheckBoxEvent, ESimCheckBoxState, SimCheckBoxState);

/**
 * @class	USimCheckBox
 * @brief	기본 체크 박스
 */
UCLASS()
class SIM_PALETTE_API USimCheckBox : public USimBaseCheckBox
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual void SynchronizeProperties() override;
#endif

public:
	void	SetUiUniqueId(int32 InId) { UiUniqueId = InId; };
	int32	GetUiUniqueId() { return UiUniqueId; };

	void	SetIsHovered(bool InIsHovered) { IsHovered = InIsHovered; };
	bool	GetIsHovered() { return IsHovered; };

	void	SetIsPressed(bool InIsPressed) { IsPressed = InIsPressed; };
	bool	GetIsPressed() { return IsPressed; };

private:
	void BroadcastSimCheckBox();

	ESimCheckBoxState GetSimCheckBoxState();
	
	UFUNCTION()
	void CheckBoxSlateOnCheckStateChangedCallback(ECheckBoxState InNewState);

	UFUNCTION()
	void OnHovered(bool InIsHorvered);

	UFUNCTION()
	void OnPressed(bool InIsPressed);

	bool IsHovered = false;
	bool IsPressed = false;
	int32 UiUniqueId = -1;

public:
	FOnSimCheckBoxStateChanged OnSimCheckBoxStateChanged;
	FOnSimCheckBoxEvent OnSimCheckBoxEvent;

#if WITH_EDITOR
public:
	virtual const FText GetPaletteCategory() override;
#endif
};
