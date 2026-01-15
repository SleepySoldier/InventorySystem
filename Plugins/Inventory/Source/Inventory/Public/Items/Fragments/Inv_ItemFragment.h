#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "IAutomationReport.h"
#include "Inv_ItemFragment.generated.h"


USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()


	/*
	 * This is the rule of 5 with move operators. search "move constructors and move assignment operators"
	 * If you declare one of the operators, you should call all of them.
	 * Need this move operators to be able to use the virtual destructor on this struct. If a child of this struct needs
	 * to be destroyed, It can, and it wont effect any of its relatives. **I think.
	 * Deleting a child through a polymorphic pointer, this is needed.
	 */
	FInv_ItemFragment() {}
	FInv_ItemFragment(const FInv_ItemFragment&) = default;
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;
	FInv_ItemFragment(FInv_ItemFragment&&) = default;
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;
	virtual ~FInv_ItemFragment() {}

	FGameplayTag GetFragmentTag() const {return FragmentTag;}
	void SetFragmentTag(FGameplayTag Tag) {FragmentTag = Tag;}
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
	
};

/*-----------------------------------------------------------*/
USTRUCT(BlueprintType)
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FIntPoint GetGridSize() const {return GridSize;}
	void SetGridSize(FIntPoint Size) {GridSize = Size;}
	float GetGridPadding() const {return GridPadding;}
	void SetGridPadding(float Padding) {GridPadding = Padding;}

	
private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FIntPoint GridSize {1,1};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	float GridPadding {0.f};
};

/*-----------------------------------------------------------*/

USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	UTexture2D* GetImage() const { return ItemIcon; }
	
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> ItemIcon {nullptr};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FVector2D IconDimensions{44.f, 44.f};
};

/*-----------------------------------------------------------*/

USTRUCT(BlueprintType)
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	int32 GetMaxStackSize() const {return MaxStackSize;}
	int32 GetStackCount() const {return StackCount;}
	void SetStackCount(int32 Count) {StackCount = Count;}
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxStackSize{1};
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 StackCount{1};

};