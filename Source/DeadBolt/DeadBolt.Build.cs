// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeadBolt : ModuleRules
{
	public DeadBolt(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
