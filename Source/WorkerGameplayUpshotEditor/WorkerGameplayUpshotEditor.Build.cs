// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WorkerGameplayUpshotEditor : ModuleRules
{
	public WorkerGameplayUpshotEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"GameplayTags",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"GameplayTagsEditor",
				"GameplayConceptEditor",
				"WorkerUpstreamNotifyEditor",
				"WorkerGameplayUpshotRuntime",
			}
		);
	}
}