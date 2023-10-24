// Fill out your copyright notice in the Description page of Project Settings.


#include "SimImage.h"
#include "SimButton.h"
#include "SimCheckBox.h"

#define LOCTEXT_NAMESPACE "UMG"


USimImage::USimImage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void USimImage::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (nullptr != ConnectSimUiButton)
	{
		BindUiButtonState();
	}

	if (nullptr != ConnectSimCheckBox)
	{
		BindUiCheckBoxState();
	}
}

TSharedRef<SWidget> USimImage::RebuildWidget()
{
	UpdateImageStyle();

	return Super::RebuildWidget();
}

void USimImage::ReleaseSlateResources(bool bReleaseChildren)
{
	if (nullptr != ConnectSimUiButton)
	{
		UnbindUiButtonState();
	}

	if (nullptr != ConnectSimCheckBox)
	{
		UnbindUiCheckBoxState();
	}

	Super::ReleaseSlateResources(bReleaseChildren);
}

void USimImage::UpdateImageStyle()
{
	if (nullptr == ConnectSimUiButton && nullptr == ConnectSimCheckBox)
		return;

	SetBrushImage(IsEnableConnect()
		? NormalImage
		: DisabledImage);
}

void USimImage::SetBrushImage(FSlateBrush InBrush)
{
	SetBrush(InBrush);

	if (ImageSizeX != 0 && ImageSizeY != 0)
	{
		SetDesiredSizeOverride(FVector2D(ImageSizeX, ImageSizeY));
	}
	else
	{
		SetDesiredSizeOverride(FVector2D(InBrush.GetImageSize()));
	}
}

void USimImage::BindUiButtonState()
{
	UnbindUiButtonState();

	ConnectSimUiButton->OnClicked.AddDynamic(this, &USimImage::OnClick);
	ConnectSimUiButton->OnHovered.AddDynamic(this, &USimImage::OnHovered);
	ConnectSimUiButton->OnPressed.AddDynamic(this, &USimImage::OnPressed);
	ConnectSimUiButton->OnReleased.AddDynamic(this, &USimImage::OnReleased);
	ConnectSimUiButton->OnUnhovered.AddDynamic(this, &USimImage::OnNormal);
	ConnectSimUiButton->OnSetIsEnable.AddDynamic(this, &USimImage::OnIsEnable);
}

void USimImage::BindUiCheckBoxState()
{
	UnbindUiCheckBoxState();

	ConnectSimCheckBox->OnSimCheckBoxEvent.AddDynamic(this, &USimImage::OnCheckBoxState);
}

void USimImage::UnbindUiButtonState()
{
	ConnectSimUiButton->OnClicked.RemoveDynamic(this, &USimImage::OnClick);
	ConnectSimUiButton->OnHovered.RemoveDynamic(this, &USimImage::OnHovered);
	ConnectSimUiButton->OnPressed.RemoveDynamic(this, &USimImage::OnPressed);
	ConnectSimUiButton->OnReleased.RemoveDynamic(this, &USimImage::OnReleased);
	ConnectSimUiButton->OnUnhovered.RemoveDynamic(this, &USimImage::OnNormal);
	ConnectSimUiButton->OnSetIsEnable.RemoveDynamic(this, &USimImage::OnIsEnable);
}

void USimImage::UnbindUiCheckBoxState()
{
	ConnectSimCheckBox->OnSimCheckBoxEvent.RemoveDynamic(this, &USimImage::OnCheckBoxState);
}

bool USimImage::IsEnableConnect()
{
	if (nullptr != ConnectSimUiButton)
		return ConnectSimUiButton->GetIsEnabled();

	if (nullptr != ConnectSimCheckBox)
		return ConnectSimCheckBox->GetIsEnabled();

	return false;
}

void USimImage::OnClick()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(PressedImage);
}

void USimImage::OnHovered()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(HoveredImage);
}

void USimImage::OnPressed()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(PressedImage);
}

void USimImage::OnReleased()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(PressedImage);
}

void USimImage::OnNormal()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(NormalImage);
}

void USimImage::OnIsEnable(bool InIsEnable)
{
	SetBrushImage(InIsEnable
		? NormalImage
		: DisabledImage);
}

void USimImage::OnSelectedNormal()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(SelectedNormalImage);
}

void USimImage::OnSelectedHovered()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(SelectedHoverImage);
}

void USimImage::OnSelectedPressed()
{
	if (IsEnableConnect() == false)	return;

	SetBrushImage(SelectedPressedImage);
}

void USimImage::OnCheckBoxState(ESimCheckBoxState InCheckBoxState)
{
	switch (InCheckBoxState)
	{
		case ESimCheckBoxState::Normal:					OnNormal();				break;
		case ESimCheckBoxState::Hovered:				OnHovered();			break;
		case ESimCheckBoxState::Pressed:				OnPressed();			break;
		case ESimCheckBoxState::Disabled:				OnIsEnable(false);		break;
		case ESimCheckBoxState::SelectedNormal:			OnSelectedNormal();		break;
		case ESimCheckBoxState::SelectedHovered:		OnSelectedHovered();	break;
		case ESimCheckBoxState::SelectedPressed:		OnSelectedPressed();	break;
	}
}

#if WITH_EDITOR
const FText USimImage::GetPaletteCategory()
{
	return LOCTEXT("", "SimPalette");
}
#endif

#undef  LOCTEXT_NAMESPACE