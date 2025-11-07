// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_InventoryItem;
class UInv_InventoryBaseWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UInv_InventoryItem*, Item);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_InventoryComponent();
	virtual void BeginPlay() override;

	void ToggleInventoryMenu();
	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	
protected:
	

private:

	TWeakObjectPtr<APlayerController> OwningController;
	
	void ConstructInventory();
	
	UPROPERTY()
	TObjectPtr<UInv_InventoryBaseWidget> InventoryMenu;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UInv_InventoryBaseWidget> InventoryMenuClass;

	bool bInventoryMenuOpen = false;
	void OpenInventoryMenu();
	void CloseInventoryMenu();
};
