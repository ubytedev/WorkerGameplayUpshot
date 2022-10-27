// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

using UnrealBuildTool;

public class WorkerGameplayUpshotRuntime : ModuleRules
{
	public WorkerGameplayUpshotRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"GameplayTags",
				"GenericActivityRuntime",
				"WorkerUpstreamNotifyRuntime", 
				"GameplayTypeLayout",
				"TypedTagStaticImpl",
				"StructUtils",
			}
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine"
			}
			);
	}
}
