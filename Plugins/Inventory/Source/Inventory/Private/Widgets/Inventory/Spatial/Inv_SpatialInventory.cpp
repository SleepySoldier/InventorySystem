// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
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
	return FInv_SlotAvailabilityResult();
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
	DisableButton(Button);
	Switcher->SetActiveWidget(Grid);
}
