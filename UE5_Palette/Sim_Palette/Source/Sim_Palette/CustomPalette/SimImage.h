// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// engine
#include <CoreMinimal.h>
#include <Components/Image.h>

// generated
#include "SimImage.generated.h"

class USimButton;
class USimCheckBox;

/**
 * @class	USimImage
 * @brief	버튼에 상태의 따른 이미지 변환
 */
UCLASS()
class SIM_PALETTE_API USimImage : public UImage
{
	GENERATED_UCLASS_BODY()
	
protected:
	virtual void OnWidgetRebuilt() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	FORCEINLINE void SetNormalImage(FSlateBrush InImage) { NormalImage = InImage; };
	FORCEINLINE void SetHoveredImage(FSlateBrush InImage) { HoveredImage = InImage; }
	FORCEINLINE void SetPressedImage(FSlateBrush InImage) { PressedImage = InImage; }
	FORCEINLINE void SetSelectedNormalImage(FSlateBrush InImage) { SelectedNormalImage = InImage; }
	FORCEINLINE void SetSelectedHoverImage(FSlateBrush InImage) { SelectedHoverImage = InImage; }
	FORCEINLINE void SetSelectedPressedImage(FSlateBrush InImage) { SelectedPressedImage = InImage; }
	FORCEINLINE void SetDisabledImage(FSlateBrush InImage) { DisabledImage = InImage; }

private:
	void UpdateImageStyle();
	void SetBrushImage(FSlateBrush InBrush);
		 
	void BindUiButtonState();
	void BindUiCheckBoxState();
		 
	void UnbindUiButtonState();
	void UnbindUiCheckBoxState();
		 
	bool IsEnableConnect();
		 
	int32 ImageSizeX = 0.f;
	int32 ImageSizeY = 0.f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Connect")
	TObjectPtr<USimButton> ConnectSimUiButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Connect")
	TObjectPtr<USimCheckBox> ConnectSimCheckBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Style")
	FSlateBrush NormalImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Style")
	FSlateBrush HoveredImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Style")
	FSlateBrush PressedImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Style")
	FSlateBrush	SelectedNormalImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Style")
	FSlateBrush	SelectedHoverImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Style")
	FSlateBrush	SelectedPressedImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SimPalette|Style")
	FSlateBrush DisabledImage;

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
