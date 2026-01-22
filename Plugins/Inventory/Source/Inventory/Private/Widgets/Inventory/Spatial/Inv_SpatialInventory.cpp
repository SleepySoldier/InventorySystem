// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"

#include "Inventory.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"

void UInv_SpatialInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Equipable->OnClicked.AddDynamic(this,&ThisClass::ShowEquipable);
	Button_Consumable->OnClicked.AddDynamic(this,&ThisClass::ShowConsumables);
	Button_Craftable->OnClicked.AddDynamic(this,&ThisClass::ShowCraftables);
	ShowEquipable();
}

FInv_SlotAvailabilityResult UInv_SpatialInventory::HasRoomForItem(UInv_ItemComponent* ItemComponent) const
{
	switch (UInv_InventoryStatics::GetItemCategoryFromItemComp(ItemComponent))
	{
		case EInv_ItemCategory::Equipable:
			return Grid_Equipable->HasRoomForItem(ItemComponent);
		case EInv_ItemCategory::Consumable:
			return Grid_Consumable->HasRoomForItem(ItemComponent);
		case EInv_ItemCategory::Craftable:
			return Grid_Craftable->HasRoomForItem(ItemComponent);
		default:
		UE_LOG(LogInventory, Error, TEXT("Item comp doesnt have a valid category"));
			return FInv_SlotAvailabilityResult();
	}

}

void UInv_SpatialInventory::ShowEquipable()
{
	SetActiveGrid(Grid_Equipable, Button_Equipable);
}

void UInv_SpatialInventory::ShowConsumables()
{
	SetActiveGrid(Grid_Consumable, Button_Consumable);
}

void UInv_SpatialInventory::ShowCraftables()
{
	SetActiveGrid(Grid_Craftable, Button_Craftable);
}

void UInv_SpatialInventory::DisableButton(UButton* Button) const
{
	Button_Equipable->SetIsEnabled(true);
	Button_Consumable->SetIsEnabled(true);
	Button_Craftable->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

void UInv_SpatialInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button)
{
	if (ActiveGrid.IsValid()) ActiveGrid->HideCursor();
	ActiveGrid = Grid;
	if (ActiveGrid.IsValid()) ActiveGrid->ShowCursor();
	DisableButton(Button);
	Switcher->SetActiveWidget(Grid);
}
