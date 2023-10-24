// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimBaseCheckBox.h"
#include "SSimCheckBox.h"

#include <Widgets/SNullWidget.h>
#include <Widgets/DeclarativeSyntaxSupport.h>
#include <Slate/SlateBrushAsset.h>
#include <Styling/UMGCoreStyle.h>

#include UE_INLINE_GENERATED_CPP_BY_NAME(SimBaseCheckBox)

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// USimBaseCheckBox

static FCheckBoxStyle* DefaultCheckboxStyle = nullptr;

#if WITH_EDITOR
static FCheckBoxStyle* EditorCheckboxStyle = nullptr;
#endif 

USimBaseCheckBox::USimBaseCheckBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (DefaultCheckboxStyle == nullptr)
	{
		DefaultCheckboxStyle = new FCheckBoxStyle(FUMGCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("Checkbox"));

		// Unlink UMG default colors.
		DefaultCheckboxStyle->UnlinkColors();
	}

	PRAGMA_DISABLE_DEPRECATION_WARNINGS
		WidgetStyle = *DefaultCheckboxStyle;

#if WITH_EDITOR 
	if (EditorCheckboxStyle == nullptr)
	{
		EditorCheckboxStyle = new FCheckBoxStyle(FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("Checkbox"));

		// Unlink UMG Editor colors from the editor settings colors.
		EditorCheckboxStyle->UnlinkColors();
	}

	if (IsEditorWidget())
	{
		WidgetStyle = *EditorCheckboxStyle;

		// The CDO isn't an editor widget and thus won't use the editor style, call post edit change to mark difference from CDO
		PostEditChange();
	}
#endif // WITH_EDITOR

	CheckedState = ECheckBoxState::Unchecked;

	HorizontalAlignment = HAlign_Fill;

	ClickMethod = EButtonClickMethod::DownAndUp;
	TouchMethod = EButtonTouchMethod::DownAndUp;
	PressMethod = EButtonPressMethod::DownAndUp;

	IsFocusable = true;
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
#if WITH_EDITORONLY_DATA
		AccessibleBehavior = ESlateAccessibleBehavior::Summary;
	bCanChildrenBeAccessible = false;
#endif
}

void USimBaseCheckBox::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyCheckbox.Reset();
}

TSharedRef<SWidget> USimBaseCheckBox::RebuildWidget()
{
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
		MyCheckbox = SNew(SSimCheckBox)
		.OnCheckStateChanged(BIND_UOBJECT_DELEGATE(FOnCheckStateChanged, SlateOnCheckStateChangedCallback))
		.Style(&WidgetStyle)
		.HAlign(HorizontalAlignment)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.PressMethod(PressMethod)
		.IsFocusable(IsFocusable)
		;
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

		if (GetChildrenCount() > 0)
		{
			MyCheckbox->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
		}

	return MyCheckbox.ToSharedRef();
}

void USimBaseCheckBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (!MyCheckbox.IsValid())
	{
		return;
	}

	PRAGMA_DISABLE_DEPRECATION_WARNINGS
		MyCheckbox->SetStyle(&WidgetStyle);
	MyCheckbox->SetIsChecked(PROPERTY_BINDING(ECheckBoxState, CheckedState));
	MyCheckbox->SetClickMethod(ClickMethod);
	MyCheckbox->SetTouchMethod(TouchMethod);
	MyCheckbox->SetPressMethod(PressMethod);
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
}

void USimBaseCheckBox::OnSlotAdded(UPanelSlot* InSlot)
{
	// Add the child to the live slot if it already exists
	if (MyCheckbox.IsValid())
	{
		MyCheckbox->SetContent(InSlot->Content ? InSlot->Content->TakeWidget() : SNullWidget::NullWidget);
	}
}

void USimBaseCheckBox::OnSlotRemoved(UPanelSlot* InSlot)
{
	// Remove the widget from the live slot if it exists.
	if (MyCheckbox.IsValid())
	{
		MyCheckbox->SetContent(SNullWidget::NullWidget);
	}
}

bool USimBaseCheckBox::IsPressed() const
{
	if (MyCheckbox.IsValid())
	{
		return MyCheckbox->IsPressed();
	}

	return false;
}


PRAGMA_DISABLE_DEPRECATION_WARNINGS
EButtonClickMethod::Type USimBaseCheckBox::GetClickMethod() const
{
	return ClickMethod;
}

void USimBaseCheckBox::SetClickMethod(EButtonClickMethod::Type InClickMethod)
{
	ClickMethod = InClickMethod;
	if (MyCheckbox.IsValid())
	{
		MyCheckbox->SetClickMethod(ClickMethod);
	}
}

EButtonTouchMethod::Type USimBaseCheckBox::GetTouchMethod() const
{
	return TouchMethod;
}

void USimBaseCheckBox::SetTouchMethod(EButtonTouchMethod::Type InTouchMethod)
{
	TouchMethod = InTouchMethod;
	if (MyCheckbox.IsValid())
	{
		MyCheckbox->SetTouchMethod(TouchMethod);
	}
}

void USimBaseCheckBox::SetPressMethod(EButtonPressMethod::Type InPressMethod)
{
	PressMethod = InPressMethod;
	if (MyCheckbox.IsValid())
	{
		MyCheckbox->SetPressMethod(PressMethod);
	}
}

EButtonPressMethod::Type USimBaseCheckBox::GetPressMethod() const
{
	return PressMethod;
}

bool USimBaseCheckBox::IsChecked() const
{
	if (MyCheckbox.IsValid())
	{
		return MyCheckbox->IsChecked();
	}

	return (CheckedState == ECheckBoxState::Checked);
}

ECheckBoxState USimBaseCheckBox::GetCheckedState() const
{
	if (MyCheckbox.IsValid())
	{
		return MyCheckbox->GetCheckedState();
	}

	return CheckedState;
}

void USimBaseCheckBox::SetIsChecked(bool InIsChecked)
{
	ECheckBoxState NewState = InIsChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	if (NewState != CheckedState)
	{
		CheckedState = NewState;
		BroadcastFieldValueChanged(FFieldNotificationClassDescriptor::CheckedState);
	}

	if (MyCheckbox.IsValid())
	{
		MyCheckbox->SetIsChecked(PROPERTY_BINDING(ECheckBoxState, CheckedState));
	}
}

void USimBaseCheckBox::SetCheckedState(ECheckBoxState InCheckedState)
{
	if (CheckedState != InCheckedState)
	{
		CheckedState = InCheckedState;
		BroadcastFieldValueChanged(FFieldNotificationClassDescriptor::CheckedState);
	}

	if (MyCheckbox.IsValid())
	{
		MyCheckbox->SetIsChecked(PROPERTY_BINDING(ECheckBoxState, CheckedState));
	}
}

const FCheckBoxStyle& USimBaseCheckBox::GetWidgetStyle() const
{
	return WidgetStyle;
}

void USimBaseCheckBox::SetWidgetStyle(const FCheckBoxStyle& InStyle)
{
	WidgetStyle = InStyle;

	if (MyCheckbox)
	{
		MyCheckbox->SetStyle(&WidgetStyle);
	}
}

bool USimBaseCheckBox::GetIsFocusable() const
{
	return IsFocusable;
}

void USimBaseCheckBox::InitIsFocusable(bool InIsFocusable)
{
	ensureMsgf(!MyCheckbox.IsValid(), TEXT("The widget is already created."));
	IsFocusable = InIsFocusable;
}

void USimBaseCheckBox::InitCheckedStateDelegate(FGetCheckBoxState InCheckedStateDelegate)
{
	ensureMsgf(!MyCheckbox.IsValid(), TEXT("The widget is already created."));
	CheckedStateDelegate = InCheckedStateDelegate;
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS

void USimBaseCheckBox::SlateOnCheckStateChangedCallback(ECheckBoxState NewState)
{
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
		if (CheckedState != NewState)
		{
			CheckedState = NewState;
			BroadcastFieldValueChanged(FFieldNotificationClassDescriptor::CheckedState);
		}
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

		const bool bWantsToBeChecked = NewState != ECheckBoxState::Unchecked;
	OnCheckStateChanged.Broadcast(bWantsToBeChecked);
}

#if WITH_ACCESSIBILITY
TSharedPtr<SWidget> USimBaseCheckBox::GetAccessibleWidget() const
{
	return MyCheckbox;
}
#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE

