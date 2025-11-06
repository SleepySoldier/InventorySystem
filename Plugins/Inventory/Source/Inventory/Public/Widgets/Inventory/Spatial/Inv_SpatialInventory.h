// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBaseWidget.h"
#include "Inv_SpatialInventory.generated.h"

class UButton;
class UWidgetSwitcher;
class UInv_InventoryGrid;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_SpatialInventory : public UInv_InventoryBaseWidget
{
	GENERATED_BODY()

private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> Switcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Equipable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Consumable;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InventoryGrid> Grid_Craftable;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Equipable;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Consumable;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_Craftable;
};
