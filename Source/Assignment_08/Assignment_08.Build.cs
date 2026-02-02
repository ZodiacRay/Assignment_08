// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Assignment_08 : ModuleRules
{
	public Assignment_08(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate",
			"GameplayTags",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Assignment_08",
			"Assignment_08/Variant_Strategy",
			"Assignment_08/Variant_Strategy/UI",
			"Assignment_08/Variant_TwinStick",
			"Assignment_08/Variant_TwinStick/AI",
			"Assignment_08/Variant_TwinStick/Gameplay",
			"Assignment_08/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
