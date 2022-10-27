// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructView.h"
#include "TypedTag.h"
#include "InstancedStruct.h"
#include "WorkerUpstreamNotifySubsystem.h"
#include "Fragment/GenericActivityFrameworkFragments.h"
#include "WorkerGameplayUpshot.generated.h"

class IGenericAgentActivityWorker;
class IGenericCrowdActivityWorker;
class IGenericWorldActivityWorker;

USTRUCT(Meta = (Categories = "World.GameplayUpshot"))
struct FWorldGameplayUpshotTag : public FWorldNotifyTag
{
	GENERATED_BODY()
	END_TYPED_TAG_DECL(FWorldGameplayUpshotTag, TEXT("World.GameplayUpshot"))
};

USTRUCT(Meta = (Categories = "Crowd.GameplayUpshot"))
struct FCrowdGameplayUpshotTag : public FCrowdNotifyTag
{
	GENERATED_BODY()
	END_TYPED_TAG_DECL(FCrowdGameplayUpshotTag, TEXT("Crowd.GameplayUpshot"))
};

USTRUCT(Meta = (Categories = "Agent.GameplayUpshot"))
struct FAgentGameplayUpshotTag : public FAgentNotifyTag
{
	GENERATED_BODY()
	END_TYPED_TAG_DECL(FAgentGameplayUpshotTag, TEXT("Agent.GameplayUpshot"))
};

// Experimental (future)
USTRUCT() struct FWorldGameplayUpshotFieldSetBase : public FWorldNotifyFieldSetBase { GENERATED_BODY() };
USTRUCT() struct FCrowdGameplayUpshotFieldSetBase : public FCrowdNotifyFieldSetBase { GENERATED_BODY() };
USTRUCT() struct FAgentGameplayUpshotFieldSetBase : public FAgentNotifyFieldSetBase { GENERATED_BODY() };
//~Experimental

UCLASS(NotPlaceable)
class WORKERGAMEPLAYUPSHOTRUNTIME_API UWorkerGameplayUpshotStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Notify the CrowdActivityWorker of an AgentActivityWorker about a gameplay occurrence, after AgentActivityWorker fully evaluated its consequences first.
	 * - This silently gets ignored if the CrowdActivityWorker did not listen to this Agent-specific GameplayUpshot.
	 */
	UFUNCTION(BlueprintCallable, Category = "GenericActivityFramework|GameplayUpshot", Meta = (DefaultToSelf = "AgentActivityWorker", DisplayName = "Send Gameplay Upshot (Agent Activity Worker)"))
	static void NotifyCrowdActivityWorkerGameplayUpshot(TScriptInterface<IGenericAgentActivityWorker> AgentActivityWorker, FAgentGameplayUpshotTag AgentGameplayUpshotTag);

	/**
	 * Notify the WorldActivityWorker of a CrowdActivityWorker about a gameplay occurrence, after CrowdActivityWorker fully evaluated its consequences first.
	 * - This silently gets ignored if the WorldActivityWorker did not listen to this Crowd-specific GameplayUpshot.
	 */
	UFUNCTION(BlueprintCallable, Category = "GenericActivityFramework|GameplayUpshot", Meta = (DefaultToSelf = "CrowdActivityWorker", DisplayName = "Send Gameplay Upshot (Crowd Activity Worker)"))
	static void NotifyWorldActivityWorkerGameplayUpshot(TScriptInterface<IGenericCrowdActivityWorker> CrowdActivityWorker, FCrowdGameplayUpshotTag CrowdGameplayUpshotTag);
};

//~Begin GameplayConcept fragments - EXPERIMENTAL @todo SEPARATE GITHUB BRANCH

USTRUCT(Meta = (DisplayName = "(Layout Fragment) Agent Gameplay Upshot", AutoExpandCategories = "OutgoingGameplayUpshotTagSets"))
struct WORKERGAMEPLAYUPSHOTRUNTIME_API FAgentGameplayUpshotLayoutFragment : public FAgentLayoutFragmentBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Meta = (BaseStruct = "AgentGameplayUpshotFieldSetBase", ExcludeBaseStruct))
	TArray<FInstancedStruct> OutgoingGameplayUpshotTagSets;
};

USTRUCT(Meta = (DisplayName = "(Layout Fragment) Crowd Gameplay Upshot", AutoExpandCategories = "OutgoingCrowdGameplayUpshotTagSet,IncomingAgentGameplayUpshotTagsSet"))
struct WORKERGAMEPLAYUPSHOTRUNTIME_API FCrowdGameplayUpshotLayoutFragment : public FCrowdLayoutFragmentBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Meta = (BaseStruct = "CrowdGameplayUpshotFieldSetBase", ExcludeBaseStruct))
	TArray<FInstancedStruct> OutgoingCrowdGameplayUpshotTagSet;
	
	UPROPERTY(EditDefaultsOnly, Meta = (BaseStruct = "AgentGameplayUpshotFieldSetBase", ExcludeBaseStruct))
	TArray<FInstancedStruct> IncomingAgentGameplayUpshotTagSet;
};

USTRUCT(Meta = (DisplayName = "(Layout Fragment) World Gameplay Upshot", AutoExpandCategories = "IncomingCrowdGameplayUpshotTagSets"))
struct WORKERGAMEPLAYUPSHOTRUNTIME_API FWorldGameplayUpshotLayoutFragment : public FWorldLayoutFragmentBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Meta = (BaseStruct = "CrowdGameplayUpshotFieldSetBase", ExcludeBaseStruct))
	TArray<FInstancedStruct> IncomingCrowdGameplayUpshotTagSets;
};

//~End GameplayConcept fragments
