// Fill out your copyright notice in the Description page of Project Settings.


#include "SimTextBlock.h"
#include "SimButton.h"
#include "SimCheckBox.h"

// engine
#include <Components/Overlay.h>
#include <Components/OverlaySlot.h>
#include <Engine/Font.h>
#include <Components/SizeBox.h>


#define LOCTEXT_NAMESPACE "UMG"


USimTextBlock::USimTextBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TextFlowingTime = 0;
	IsTextFlowing = false;
	TextFlowingVelocity = 2.0f;
	TextFlowingIntervalTime = 1.0f;
	IsUpdateFontCheckRaw = false;
	IsUpdateCheckCliping = false;
}

TSharedRef<SWidget> USimTextBlock::RebuildWidget()
{
	UWorld* World = GetWorld();
	if (World)
		World->GetTimerManager().SetTimer(TimerHandler, this, &USimTextBlock::UpdateTick, 0.02f, true);

	if (nullptr != ConnectSimUiButton)
	{
		BindUiButtonState();
	}

	if (nullptr != ConnectSimCheckBox)
	{
		BindUiCheckBoxState();
	}

	IsUpdateCheckCliping = true;

	UpdateTextStyle();

	return Super::RebuildWidget();
}

void USimTextBlock::ReleaseSlateResources(bool bReleaseChildren)
{
	UWorld* World = GetWorld();
	if (World && TimerHandler.IsValid())
		World->GetTimerManager().ClearTimer(TimerHandler);

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

void USimTextBlock::SetText(FText InText)
{
	FText NewText = FText::AsCultureInvariant(InText.ToString().ReplaceEscapedCharWithChar());

	Super::SetText(NewText);
}

void USimTextBlock::SetText(FString InText)
{
	SetText(FText::FromString(InText));
}

void USimTextBlock::SetText(int32 InText)
{
	SetText(FText::FromString(FString::FromInt(InText)));
}


void USimTextBlock::UpdateTick()
{
	if (this->GetVisibility() == ESlateVisibility::Collapsed)
		return;

	if (IsUpdateCheckCliping)
	{
		IsUpdateCheckCliping = false;
		CheckCliping();
	}

	if (IsTextFlowing)
	{
		const FGeometry& MyGeometry = this->GetCachedGeometry();

		UOverlay* ParentOverlay = Cast<UOverlay>(this->GetParent());
		if (ParentOverlay != nullptr)
		{
			const FGeometry& OverlayGeometry = ParentOverlay->GetCachedGeometry();

			if (OverlayGeometry.Size.X > MyGeometry.Size.X)
			{
				FVector2D RanderPosition = this->GetRenderTransform().Translation;
				if (RanderPosition.X > 0.f || RanderPosition.X < 0.f)
				{
					RanderPosition.X = 0.f;
					this->SetRenderTranslation(RanderPosition);
				}
			}
			else
			{
				FVector2D RanderPosition = this->GetRenderTransform().Translation;
				float CurPositionX = RanderPosition.X;
				RanderPosition.X = RanderPosition.X - TextFlowingVelocity;

				if (CurPositionX >= 0.0f && RanderPosition.X < 0.0f)
				{
					FTimespan timespan = FDateTime::FromUnixTimestamp(FDateTime::UtcNow().ToUnixTimestamp()) - FDateTime::FromUnixTimestamp(TextFlowingTime);
					if (timespan.GetTotalSeconds() < TextFlowingIntervalTime)
						return;
				}

				if (FMath::Abs(RanderPosition.X) - FMath::Abs(OverlayGeometry.Size.X) >= 0.f)
				{
					RanderPosition.X = OverlayGeometry.Size.X;
				}

				TextFlowingTime = FDateTime::UtcNow().ToUnixTimestamp();
				this->SetRenderTranslation(RanderPosition);
			}
		}
	}
}

void USimTextBlock::UpdateTextStyle()
{
	if (nullptr == ConnectSimUiButton && nullptr == ConnectSimCheckBox)
		return;

	SetColorAndOpacity(IsEnableConnect()
		? NormalTextColor
		: DisabledTextColor);
}

void USimTextBlock::BindUiButtonState()
{
	UnbindUiButtonState();

	ConnectSimUiButton->OnClicked.AddDynamic(this, &USimTextBlock::OnClick);
	ConnectSimUiButton->OnHovered.AddDynamic(this, &USimTextBlock::OnHovered);
	ConnectSimUiButton->OnPressed.AddDynamic(this, &USimTextBlock::OnPressed);
	ConnectSimUiButton->OnReleased.AddDynamic(this, &USimTextBlock::OnReleased);
	ConnectSimUiButton->OnUnhovered.AddDynamic(this, &USimTextBlock::OnNormal);
	ConnectSimUiButton->OnSetIsEnable.AddDynamic(this, &USimTextBlock::OnIsEnable);
}

void USimTextBlock::BindUiCheckBoxState()
{
	UnbindUiCheckBoxState();

	ConnectSimCheckBox->OnSimCheckBoxEvent.AddDynamic(this, &USimTextBlock::OnCheckBoxState);
}

void USimTextBlock::UnbindUiButtonState()
{
	ConnectSimUiButton->OnClicked.RemoveDynamic(this, &USimTextBlock::OnClick);
	ConnectSimUiButton->OnHovered.RemoveDynamic(this, &USimTextBlock::OnHovered);
	ConnectSimUiButton->OnPressed.RemoveDynamic(this, &USimTextBlock::OnPressed);
	ConnectSimUiButton->OnReleased.RemoveDynamic(this, &USimTextBlock::OnReleased);
	ConnectSimUiButton->OnUnhovered.RemoveDynamic(this, &USimTextBlock::OnNormal);
	ConnectSimUiButton->OnSetIsEnable.RemoveDynamic(this, &USimTextBlock::OnIsEnable);
}

void USimTextBlock::UnbindUiCheckBoxState()
{
	ConnectSimCheckBox->OnSimCheckBoxEvent.RemoveDynamic(this, &USimTextBlock::OnCheckBoxState);
}

bool USimTextBlock::IsEnableConnect()
{
	if (nullptr != ConnectSimUiButton)
		return ConnectSimUiButton->GetIsEnabled();

	if (nullptr != ConnectSimCheckBox)
		return ConnectSimCheckBox->GetIsEnabled();

	return false;
}

void USimTextBlock::CheckCliping()
{
	USizeBox* ParentSizeBox = Cast<USizeBox>(this->GetParent());
	if (ParentSizeBox == nullptr)
		return;

	if (ParentSizeBox->GetWidthOverride() > 0)
	{
		SetClipping(EWidgetClipping::ClipToBounds);
	}
	else
	{
		SetClipping(EWidgetClipping::Inherit);
	}
}

void USimTextBlock::OnClick()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(PressedTextColor);
}

void USimTextBlock::OnHovered()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(HoveredTextColor);
}

void USimTextBlock::OnPressed()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(PressedTextColor);
}

void USimTextBlock::OnReleased()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(NormalTextColor);
}

void USimTextBlock::OnNormal()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(NormalTextColor);
}

void USimTextBlock::OnIsEnable(bool IsEnableIn)
{
	SetColorAndOpacity(IsEnableIn
		? NormalTextColor
		: DisabledTextColor);
}

void USimTextBlock::OnSelectedNormal()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(SelectedNormalTextColor);
}

void USimTextBlock::OnSelectedHovered()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(SelectedHoverTextColor);
}

void USimTextBlock::OnSelectedPressed()
{
	if (IsEnableConnect() == false)	return;

	SetColorAndOpacity(SelectedPressedTextColor);
}

void USimTextBlock::OnCheckBoxState(ESimCheckBoxState InCheckBoxState)
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
const FText USimTextBlock::GetPaletteCategory()
{
	return LOCTEXT("", "SimPalette");
}
#endif

#undef  LOCTEXT_NAMESPACE