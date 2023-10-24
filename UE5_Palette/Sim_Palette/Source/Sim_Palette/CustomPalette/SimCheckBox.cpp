// Fill out your copyright notice in the Description page of Project Settings.


#include "SimCheckBox.h"

#define LOCTEXT_NAMESPACE "UMG"

TSharedRef<SWidget> USimCheckBox::RebuildWidget()
{
	MyCheckbox = SNew(SSimCheckBox)
		.OnCheckStateChanged(BIND_UOBJECT_DELEGATE(FOnCheckStateChanged, CheckBoxSlateOnCheckStateChangedCallback))
		.Style(&GetWidgetStyle())
		.HAlign(HorizontalAlignment)
		.ClickMethod(GetClickMethod())
		.TouchMethod(GetTouchMethod())
		.PressMethod(GetPressMethod())
		.IsFocusable(GetIsFocusable())
		;

	if (GetChildrenCount() > 0)
	{
		MyCheckbox->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
	}

	MyCheckbox->SetSimCheckBoxHovered(FOnSimSCheckBoxHovered::CreateUObject(this, &USimCheckBox::OnHovered));
	MyCheckbox->SetSimCheckBoxPressed(FOnSimSCheckBoxPressed::CreateUObject(this, &USimCheckBox::OnPressed));

	return MyCheckbox.ToSharedRef();
}

void USimCheckBox::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	if (MyCheckbox.IsValid())
	{
		MyCheckbox->Clear();
		MyCheckbox.Reset();
	}
}

#if WITH_EDITOR
void USimCheckBox::SynchronizeProperties()
{
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	if (CheckedState != GetCheckedState())
	{
		CheckBoxSlateOnCheckStateChangedCallback(CheckedState);
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS

	Super::SynchronizeProperties();
}

#endif

void USimCheckBox::BroadcastSimCheckBox()
{
	OnSimCheckBoxEvent.Broadcast(GetSimCheckBoxState());
}

ESimCheckBoxState USimCheckBox::GetSimCheckBoxState()
{
	ECheckBoxState CurrentBoxState = MyCheckbox->GetCheckedState();

	if (GetIsEnabled() == false)
		return ESimCheckBoxState::Disabled;

	switch (CurrentBoxState)
	{
		case ECheckBoxState::Unchecked:
		{
			if (GetIsPressed())			return ESimCheckBoxState::Pressed;
			if (GetIsHovered())			return ESimCheckBoxState::Hovered;

			return ESimCheckBoxState::Normal;
		}

		case ECheckBoxState::Checked:
		{
			if (GetIsPressed())			return ESimCheckBoxState::SelectedPressed;
			if (GetIsHovered())			return ESimCheckBoxState::SelectedHovered;

			return ESimCheckBoxState::SelectedNormal;
		}
	}

	return ESimCheckBoxState::None;
}

void USimCheckBox::CheckBoxSlateOnCheckStateChangedCallback(ECheckBoxState InNewState)
{
	SetCheckedState(InNewState);

	//@TODO: Choosing to treat Undetermined as Checked
	const bool bWantsToBeChecked = InNewState != ECheckBoxState::Unchecked;
	OnSimCheckBoxStateChanged.Broadcast(this, bWantsToBeChecked);
	BroadcastSimCheckBox();
}

void USimCheckBox::OnHovered(bool InIsHorvered)
{
	SetIsHovered(InIsHorvered);

	BroadcastSimCheckBox();
}

void USimCheckBox::OnPressed(bool InIsPressed)
{
	SetIsPressed(InIsPressed);

	BroadcastSimCheckBox();
}

#if WITH_EDITOR
const FText USimCheckBox::GetPaletteCategory()
{
	return LOCTEXT("", "SimPalette");
}
#endif

#undef  LOCTEXT_NAMESPACE