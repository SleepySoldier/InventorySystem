// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/ItemPopup/Inv_ItemPopup.h"
#include "Components/Image.h"

void UInv_GridSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	GridSlotHovered.Broadcast(TileIndex, InMouseEvent);
}

void UInv_GridSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	GridSlotUnHovered.Broadcast(TileIndex, InMouseEvent);
}

FReply UInv_GridSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	GridSlotClicked.Broadcast(TileIndex, InMouseEvent);
	return FReply::Handled();
}

void UInv_GridSlot::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
}

void UInv_GridSlot::SetItemPopup(UInv_ItemPopup* Popup)
{
	ItemPopup = Popup;
	ItemPopup->SetGridIndex(GetIndex());
	ItemPopup->OnNativeDestruct.AddUObject(this, &ThisClass::OnItemPopupDestruct);
}

UInv_ItemPopup* UInv_GridSlot::GetItemPopup() const
{
	return ItemPopup.Get(); 
}

void UInv_GridSlot::SetOccupiedTexture()
{
	GridSlotState = EInv_GridslotState::Occupied;
	Image_GridSlot->SetBrush(Brush_Occupied);
}

void UInv_GridSlot::SetUnoccupiedTexture()
{
	GridSlotState = EInv_GridslotState::Unoccupied;
	Image_GridSlot->SetBrush(Brush_Unoccupied);
}

void UInv_GridSlot::SetSelectedTexture()
{
	GridSlotState = EInv_GridslotState::Selected;
	Image_GridSlot->SetBrush(Brush_Selected);
}

void UInv_GridSlot::SetGreyedOutTexture()
{
	GridSlotState = EInv_GridslotState::GreyedOut;
	Image_GridSlot->SetBrush(Brush_GreyedOut);
}

void UInv_GridSlot::OnItemPopupDestruct(UUserWidget* Menu)
{
	ItemPopup.Reset();
}
