// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_Network : ModuleRules
{
	public FPS_Network(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NetCore","GameplayAbilities","GameplayTags","GameplayTagsEditor","GameplayTasks","HeadMountedDisplay", "EnhancedInput" });
	}
}
