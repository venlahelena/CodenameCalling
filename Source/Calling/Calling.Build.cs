// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Calling : ModuleRules
{
	public Calling(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameplayAbilities" });
        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks" });
    }
}
