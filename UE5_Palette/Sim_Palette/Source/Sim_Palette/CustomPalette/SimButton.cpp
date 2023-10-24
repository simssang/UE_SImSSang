// Fill out your copyright notice in the Description page of Project Settings.


#include "SimButton.h"

// engine
#include <Components/ButtonSlot.h>
#include <Sound/SlateSound.h>
#include <Widgets/Input/SButton.h>

#define LOCTEXT_NAMESPACE "UMG"

USimButton::USimButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

TSharedRef<SWidget> USimButton::RebuildWidget()
{
	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateClickHandler))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlatePressedHandler))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateReleasedHandler))
		.OnHovered_UObject(this, &USimButton::SlateHoveredHandler)
		.OnUnhovered_UObject(this, &USimButton::SlateUnhoveredHandler)
		.IsFocusable(GetIsFocusable());

	MyButton->SetButtonStyle(&GetStyle());
	MyButton->SetClickMethod(GetClickMethod());
	MyButton->SetTouchMethod(GetTouchMethod());
	MyButton->SetPressMethod(GetPressMethod());

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}

	return MyButton.ToSharedRef();
}

void USimButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	UpdateStyle();
}

FReply USimButton::SlateClickHandler()
{
	NativeOnClicked();

	OnClicked.Broadcast();
	OnClickedWithIndex.Broadcast(ButtonIndex);

	return FReply::Handled();
}

void USimButton::SlatePressedHandler()
{
	NativeOnPressed();

	OnPressed.Broadcast();
}

void USimButton::SlateReleasedHandler()
{
	NativeOnReleased();

	OnReleased.Broadcast();
}

void USimButton::SlateHoveredHandler()
{
	NativeOnHovered();

	OnHovered.Broadcast();
	OnHoveredWithIndex.Broadcast(ButtonIndex);
}

void USimButton::SlateUnhoveredHandler()
{
	NativeOnUnhovered();

	OnUnhovered.Broadcast();
}

void USimButton::SetIsEnabled(bool InIsEnabled)
{
	Super::SetIsEnabled(InIsEnabled);

	OnSetIsEnable.Broadcast(InIsEnabled);
}

void USimButton::SetIsFocusable(bool InValue)
{
	InitIsFocusable(InValue);
}

void USimButton::UpdateStyle()
{
	if (MyButton.IsValid()) MyButton->SetButtonStyle(&GetStyle());
}

#if WITH_EDITOR
const FText USimButton::GetPaletteCategory()
{
	return LOCTEXT("", "SimPalette");
}
#endif

#undef  LOCTEXT_NAMESPACE