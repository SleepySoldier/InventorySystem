// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Udemy_Inventory : ModuleRules
{
	public Udemy_Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Udemy_Inventory",
			"Udemy_Inventory/Variant_Platforming",
			"Udemy_Inventory/Variant_Platforming/Animation",
			"Udemy_Inventory/Variant_Combat",
			"Udemy_Inventory/Variant_Combat/AI",
			"Udemy_Inventory/Variant_Combat/Animation",
			"Udemy_Inventory/Variant_Combat/Gameplay",
			"Udemy_Inventory/Variant_Combat/Interfaces",
			"Udemy_Inventory/Variant_Combat/UI",
			"Udemy_Inventory/Variant_SideScrolling",
			"Udemy_Inventory/Variant_SideScrolling/AI",
			"Udemy_Inventory/Variant_SideScrolling/Gameplay",
			"Udemy_Inventory/Variant_SideScrolling/Interfaces",
			"Udemy_Inventory/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
