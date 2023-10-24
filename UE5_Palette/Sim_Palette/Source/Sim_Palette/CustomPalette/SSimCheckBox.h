// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Widgets/Input/SCheckBox.h>

/**
 *
 */

DECLARE_DELEGATE_OneParam(FOnSimSCheckBoxHovered, bool);
DECLARE_DELEGATE_OneParam(FOnSimSCheckBoxPressed, bool);

class SIM_PALETTE_API SSimCheckBox : public SCheckBox
{
public:
	void SetSimCheckBoxHovered(const FOnSimSCheckBoxHovered& InOnSimCheckBoxHovered)
	{
		OnSimSCheckBoxHovered = InOnSimCheckBoxHovered;
	}

	void SetSimCheckBoxPressed(const FOnSimSCheckBoxPressed& InOnSimCheckBoxPressed)
	{
		OnSimSCheckBoxPressed = InOnSimCheckBoxPressed;
	}

	void Clear()
	{
		if (OnSimSCheckBoxHovered.IsBound())
		{
			OnSimSCheckBoxHovered.Unbind();
		}

		if (OnSimSCheckBoxPressed.IsBound())
		{
			OnSimSCheckBoxPressed.Unbind();
		}
	}

	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
	{
		if (OnSimSCheckBoxHovered.IsBound())
		{
			OnSimSCheckBoxHovered.Execute(true);
		}

		SCheckBox::OnMouseEnter(MyGeometry, MouseEvent);
	}
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent)  override
	{
		if (OnSimSCheckBoxHovered.IsBound())
		{
			OnSimSCheckBoxHovered.Execute(false);
		}

		SCheckBox::OnMouseLeave(MouseEvent);
	}

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
	{
		if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			if (OnSimSCheckBoxPressed.IsBound())
			{
				OnSimSCheckBoxPressed.Execute(true);
			}
		}

		return SCheckBox::OnMouseButtonDown(MyGeometry, MouseEvent);
	}

	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
	{
		if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			if (OnSimSCheckBoxPressed.IsBound())
			{
				OnSimSCheckBoxPressed.Execute(false);
			}
		}

		return SCheckBox::OnMouseButtonUp(MyGeometry, MouseEvent);
	}

private:
	FOnSimSCheckBoxHovered OnSimSCheckBoxHovered;
	FOnSimSCheckBoxPressed OnSimSCheckBoxPressed;
};
