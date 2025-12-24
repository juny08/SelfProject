// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SelfProject : ModuleRules
{
	public SelfProject(ReadOnlyTargetRules Target) : base(Target)
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
			"SelfProject",
			"SelfProject/Variant_Platforming",
			"SelfProject/Variant_Platforming/Animation",
			"SelfProject/Variant_Combat",
			"SelfProject/Variant_Combat/AI",
			"SelfProject/Variant_Combat/Animation",
			"SelfProject/Variant_Combat/Gameplay",
			"SelfProject/Variant_Combat/Interfaces",
			"SelfProject/Variant_Combat/UI",
			"SelfProject/Variant_SideScrolling",
			"SelfProject/Variant_SideScrolling/AI",
			"SelfProject/Variant_SideScrolling/Gameplay",
			"SelfProject/Variant_SideScrolling/Interfaces",
			"SelfProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
