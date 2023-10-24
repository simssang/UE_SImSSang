// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// engine
#include <CoreMinimal.h>
#include <Components/TextBlock.h>

// generated
#include "SimTextBlock.generated.h"

class USimButton;
class USimCheckBox;

/**
 * @class	USimTextBlock
 * @brief	기능이 추가 된 기본 텍스트 블록
 */
UCLASS()
class SIM_PALETTE_API USimTextBlock : public UTextBlock
{
	GENERATED_UCLASS_BODY()
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SetText(FText InText) override;
	
public:
	void SetText(FString InText);
	void SetText(int32 InText);

private:
	void UpdateTick();
	void UpdateTextStyle();
		 
	void BindUiButtonState();
	void BindUiCheckBoxState();
		 
	void UnbindUiButtonState();
	void UnbindUiCheckBoxState();
		 
	bool IsEnableConnect();
		 
	void CheckCliping();

	FTimerHandle TimerHandler;
	int64 TextFlowingTime;

	bool IsUpdateFontCheckRaw = false;
	bool IsUpdateCheckCliping = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Flowing")
	bool IsTextFlowing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Flowing")
	bool IsUseFormatText = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Flowing")
	float TextFlowingVelocity = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Flowing")
	float TextFlowingIntervalTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Connect")
	TObjectPtr<USimButton> ConnectSimUiButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Connect")
	TObjectPtr<USimCheckBox> ConnectSimCheckBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Style")
	FLinearColor NormalTextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Style")
	FLinearColor HoveredTextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Style")
	FLinearColor PressedTextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Style")
	FLinearColor SelectedNormalTextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Style")
	FLinearColor SelectedHoverTextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Style")
	FLinearColor SelectedPressedTextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimUIPalette|Style")
	FLinearColor DisabledTextColor = FLinearColor(0.4f, 0.4f, 0.4f, 0.8f);

public:
	FORCEINLINE void SetNormalTextColor(FLinearColor InColor)				{ NormalTextColor = InColor; }
	FORCEINLINE void SetHoveredTextColor(FLinearColor InColor)				{ HoveredTextColor = InColor; }
	FORCEINLINE void SetPressedTextColor(FLinearColor InColor)				{ PressedTextColor = InColor; }
	FORCEINLINE void SetSelectedNormalTextColor(FLinearColor InColor)		{ SelectedNormalTextColor = InColor; }
	FORCEINLINE void SetSelectedHoverTextColor(FLinearColor InColor)		{ SelectedHoverTextColor = InColor; }
	FORCEINLINE void SetSelectedPressedTextColor(FLinearColor InColor)		{ SelectedPressedTextColor = InColor; }
	FORCEINLINE void SetDisabledTextColor(FLinearColor InColor)				{ DisabledTextColor = InColor; }

public:
	UFUNCTION()
	void OnClick();

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnPressed();

	UFUNCTION()
	void OnReleased();

	UFUNCTION()
	void OnNormal();

	UFUNCTION()
	void OnIsEnable(bool InIsEnable);

	UFUNCTION()
	void OnSelectedNormal();

	UFUNCTION()
	void OnSelectedHovered();

	UFUNCTION()
	void OnSelectedPressed();

	UFUNCTION()
	void OnCheckBoxState(ESimCheckBoxState InCheckBoxState);

#if WITH_EDITOR
public:
	virtual const FText GetPaletteCategory() override;
#endif
};
