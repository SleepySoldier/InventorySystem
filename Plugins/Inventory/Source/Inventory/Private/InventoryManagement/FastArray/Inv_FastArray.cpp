#include "InventoryManagement/FastArray/Inv_FastArray.h"

TArray<UInv_InventoryItem*> FInv_InventoryFastArray::GetAllItems() const
{
	return TArray<UInv_InventoryItem*>();
}

void FInv_InventoryFastArray::PreReplicatedRemove(const TArray<int32> RemovedIndices, int32 FinalSize)
{
}

void FInv_InventoryFastArray::PostReplicatedAdd(const TArray<int32> AddedIndices, int32 FinalSize)
{
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_InventoryComponent* ItemComponent)
{
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_InventoryItem* Item)
{
}

void FInv_InventoryFastArray::RemoveEntry(UInv_InventoryItem* Item)
{
}