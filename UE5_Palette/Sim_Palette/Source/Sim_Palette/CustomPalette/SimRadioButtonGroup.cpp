// Fill out your copyright notice in the Description page of Project Settings.


#include "SimRadioButtonGroup.h"
#include "SimRadioButton.h"

#define LOCTEXT_NAMESPACE "UMG"

void USimRadioButtonGroup::PostLoad()
{
	Super::PostLoad();
	SetRadioButtons();
}

void USimRadioButtonGroup::ReleaseSlateResources(bool BReleaseChildren)
{
	Super::ReleaseSlateResources(BReleaseChildren);

	ResetRadioButtons();
}

bool USimRadioButtonGroup::IsCheckState(int32 InRadioButtonIndex, ECheckBoxState InCheckState)
{
	if (InRadioButtonIndex < RadioButtonList.Num())
	{
		TObjectPtr<USimRadioButton> radioButton = RadioButtonList[InRadioButtonIndex];
		if (nullptr != radioButton)
		{
			if (radioButton->GetCheckedState() == InCheckState)
			{
				return true;
			}
		}
	}

	return false;
}

void USimRadioButtonGroup::SetRadioButtonCheck(int32 InIndex, bool InBroadcast /*= false*/)
{
	if (InIndex < 0)
		return;

	int32 ListCount = RadioButtonList.Num();

	for (int32 i = 0; i < ListCount; ++i)
	{
		USimRadioButton* radioButton = RadioButtonList[i];
		if (nullptr != radioButton && InIndex != i)
		{
			radioButton->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}

	if (ListCount > InIndex)
	{
		TObjectPtr<USimRadioButton> radioButton = RadioButtonList[InIndex];
		if (nullptr != radioButton)
		{
			ActiveIndex = InIndex;
			radioButton->SetCheckedState(ECheckBoxState::Checked);
		}
	}

	if (InBroadcast)
	{
		if (ActiveIndex != -1)
			OnRadioButtonGroupStateChanged.Broadcast(ActiveIndex, RadioButtonList[ActiveIndex]);
	}
}

void USimRadioButtonGroup::SetRadioButtons()
{
	for (int32 i = 0; i < RadioButtonList.Num(); i++)
	{
		USimRadioButton* radioButton = RadioButtonList[i];
		if (nullptr != radioButton)
		{
			if (ActiveIndex < 0 && radioButton->IsChecked())
				ActiveIndex = i;
			else
				radioButton->SetIsChecked(false);

			radioButton->OnSimCheckBoxStateChanged.AddUniqueDynamic(this, &USimRadioButtonGroup::OnCheckBoxStateChanged);
		}
	}
}

void USimRadioButtonGroup::ResetRadioButtons()
{
	for (int32 i = 0; i < RadioButtonList.Num(); i++)
	{
		USimRadioButton* radioButton = RadioButtonList[i];
		if (nullptr != radioButton)
		{
			radioButton->OnSimCheckBoxStateChanged.RemoveDynamic(this, &USimRadioButtonGroup::OnCheckBoxStateChanged);
		}
	}

	RadioButtonList.Reset();
}

void USimRadioButtonGroup::AddRadioButton(TObjectPtr<USimRadioButton> InRadioButton)
{
	if (IsValid(InRadioButton) == false)
		return;

	RadioButtonList.Add(InRadioButton);
	InRadioButton->OnSimCheckBoxStateChanged.AddUniqueDynamic(this, &USimRadioButtonGroup::OnCheckBoxStateChanged);
}

void USimRadioButtonGroup::RemoveRadioButton(TObjectPtr<USimRadioButton> InRadioButton)
{
	for (int32 i = 0; i < RadioButtonList.Num(); i++)
	{
		USimRadioButton* radioButton = RadioButtonList[i];
		if (radioButton == InRadioButton)
		{
			radioButton->OnSimCheckBoxStateChanged.RemoveDynamic(this, &USimRadioButtonGroup::OnCheckBoxStateChanged);
			RadioButtonList.Remove(InRadioButton);
			break;
		}
	}
}

void USimRadioButtonGroup::OnCheckBoxStateChanged(const USimCheckBox* InCheckBox, const bool InIsChecked)
{
	if (nullptr == InCheckBox)
		return;

	for (auto i = 0; i < RadioButtonList.Num(); i++)
	{
		USimRadioButton* radioButton = RadioButtonList[i];
		
		if (i == ActiveIndex)
		{
			radioButton->SetIsChecked(!InIsChecked);
		}
		else if (radioButton == InCheckBox)
		{
			ActiveIndex = i;
		}
		else
		{
			radioButton->SetIsChecked(false);
		}
	}

	if (ActiveIndex != -1)
	{
		OnRadioButtonGroupStateChanged.Broadcast(ActiveIndex, RadioButtonList[ActiveIndex]);
	}
}

#if WITH_EDITOR
const FText USimRadioButtonGroup::GetPaletteCategory()
{
	return LOCTEXT("", "SimPalette");
}
#endif

#undef  LOCTEXT_NAMESPACE