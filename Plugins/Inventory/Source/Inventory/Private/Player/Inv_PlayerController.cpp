// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Inv_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Interaction/Inv_Highlightable.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUD/INV_HUDWidget.h"

AInv_PlayerController::AInv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceLength = 1000.f;
	ItemTraceChannel = ECC_GameTraceChannel1;
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceForItem();
}

void AInv_PlayerController::ToggleInventory()
{
	if (!InventoryComponent.IsValid()) return;
	InventoryComponent->ToggleInventoryMenu();
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateHUDWidget();
	InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();
}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
	// Add the mapping context to this class.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &AInv_PlayerController::PrimaryInteract);
	EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AInv_PlayerController::ToggleInventory);

}

void AInv_PlayerController::PrimaryInteract()
{
	UE_LOG(LogTemp, Display, TEXT("Primary Interact"));
}

void AInv_PlayerController::CreateHUDWidget()
{
	if (!IsLocalController()) return;

	HUDWidget = CreateWidget<UINV_HUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}

void AInv_PlayerController::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;
	FVector2D ViewportSize = FVector2D::ZeroVector;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2;

	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;

	const FVector TraceEnd =  TraceStart + Forward * TraceLength;
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ItemTraceChannel);

	LastActor = ThisActor;
	ThisActor = Hit.GetActor();

	if (!ThisActor.IsValid())
	{
		if (IsValid(HUDWidget)) HUDWidget->HidePickupMessage();
	}
	
	if (ThisActor == LastActor) return;

	if (ThisActor.IsValid())
	{
		if (UActorComponent* Highlightable = ThisActor->FindComponentByInterface(UInv_Highlightable::StaticClass()); IsValid(Highlightable))
		{
			UE_LOG(LogTemp, Warning, TEXT("Should highlight"));
			IInv_Highlightable::Execute_Highlight(Highlightable);
		}
		UInv_ItemComponent* ItemComponent = ThisActor->FindComponentByClass<UInv_ItemComponent>();
		if (!ItemComponent) return;

		if (IsValid(HUDWidget)) HUDWidget->ShowPickupMessage(ItemComponent->GetPickupMessage());
	}
	if (LastActor.IsValid())
	{
		if (UActorComponent* Highlightable = LastActor->FindComponentByInterface(UInv_Highlightable::StaticClass()); IsValid(Highlightable))
		{
			IInv_Highlightable::Execute_UnHighlight(Highlightable);
		}	
	}
}


