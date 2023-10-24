// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// engine
#include <CoreMinimal.h>
#include <Components/Button.h>

// generated
#include "SimButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimButtonClickedEventWithIndex, const int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimButtonHoveredEventWithIndex, const int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimButtonSetIsEnabled, bool, IsEnable);

/**
 * @class	USimButton
 * @brief	기본 버튼
 */
UCLASS()
class SIM_PALETTE_API USimButton : public UButton
{
	GENERATED_UCLASS_BODY()

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;

	FReply SlateClickHandler();
	void SlatePressedHandler();
	void SlateReleasedHandler();
	void SlateHoveredHandler();
	void SlateUnhoveredHandler();

	virtual void NativeOnClicked() {};
	virtual void NativeOnPressed() {};
	virtual void NativeOnReleased() {};
	virtual void NativeOnHovered() {};
	virtual void NativeOnUnhovered() {};

public:
	virtual void SetIsEnabled(bool InIsEnabled) override;

public:
	void SetIndex(int32 InIndex) { ButtonIndex = InIndex; };
	const int32 GetIndex() const { return ButtonIndex; };

	bool GetButtonFlag() { return ButtonFlag; };
	void SetButtonFlag(bool InFlag) { ButtonFlag = InFlag; };

	void SetIsFocusable(bool InValue);

private:
	void UpdateStyle();

protected:
	int32 ButtonIndex = -1;

public:
	bool ButtonFlag = false;

public:
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSimButtonClickedEventWithIndex OnClickedWithIndex;
	
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSimButtonHoveredEventWithIndex OnHoveredWithIndex;

	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnSimButtonSetIsEnabled OnSetIsEnable;

#if WITH_EDITOR
public:
	virtual const FText GetPaletteCategory() override;
#endif
};
