// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "WorkerUpstreamNotifyGameplayConcept.h"
#include "Modules/ModuleInterface.h"

/**
 * Extending GenericActivityFramework,
 * WorkerGameplayUpshot is a spin-off derivative of WorkerUpstreamNotify that is tuned for a specific static purpose.
 *
 * WorkerGameplayUpshot:
 * - Introduces a blueprint-exposed type of upstream notification called Gameplay Upshot, which encapsulates the final notice about a gameplay occurrence, after privately evaluating its consequence first.
 * - The emphasis lies on *after* evaluating its consequence first. Upshots are always publicized at *the very end* of a gameplay occurrence. Other systems can assume that this is always the case.
 *
 * For this subsystem,
 * By mapping tags to the returned strings of IWorkerGameplayUpshotGameplayConcept's remap category getter functions,
 * - You define outgoing gameplay experiences a World/Crowd/Agent can experience, and is relevant for its higher 'owner' to listen to.
 *
 * ============================================================================
 * ## Examples	@todo Elaborate more on these examples + add better examples
 * ============================================================================
 * 
 * Base Agents could have this minimum functionality: OnHostileDetected, OnDamaged.
 * - Agent.GameplayUpshot.OnHostileDetected
 * - Agent.GameplayUpshot.OnDamaged
 *
 *   1. Agent --> receive damage --> fully evaluate being damaged (subtract HP) --> SendGameplayUpshot(Agent.GameplayUpshot.OnDamaged)
 *	 2. (Recommended: The crowd activity worker decides what the Agent should do next (depending on the current CrowdActivityStrategy))
 *	  a. Crowd --> (Evaluate CrowdActivityStrategy) -->  Begin appropriate agent activity, let's say 'attack' --> prerequisite: set the scoped 'Attack target' payload instance (and adjust its AgentActivityStrategy).
 *	  b. Agent --> I will 'attack' 'attack target'.
 *	  
 *   1. Agent --> perceived pawn --> it's hostile! --> do all internal registrations --> SendGameplayUpshot(Agent.GameplayUpshot.OnHostileDetected)
 *   2. (Recommended: The crowd activity worker decides what the Agent should do next (depending on the current CrowdActivityStrategy)
 *    a. Crowd --> (Evaluate CrowdActivityStrategy) --> Begin appropriate agent activity next, let's say 'flee' --> prerequisite: set move to 'gameplay location' payload instance (and adjust its AgentActivityStrategy).
 *    b. Agent --> I will 'flee' towards 'gameplay location'.
 *
 * A Crowd might be interested in whether a member is damaged during its crowd activity, and change the course of action depending (depending on its own internal crowd activity strategy).
 * - Now, Instead of relying on the implicit assumption that a specific attribute change represents a certain gameplay occurrence, you can simply define your own outgoing gameplay occurrence, and know that it's always send *after* all the consequences were already privately evaluated first.
 */
class WORKERGAMEPLAYUPSHOTEDITOR_API IWorkerGameplayUpshotGameplayConcept : public IWorkerUpstreamNotifyGameplayConcept
{
public:
	//~ Begin IWorkerUpstreamNotifyGameplayConcept
	virtual TArray<FString> GetWorldNotifyBaseRemapCategories() const override
	{
		// This might not even be necessary, since it's already the highest in the world-crowd-agent chain,
		// (but you still might add functionality to notify the GameInstance, GameMode, or level blueprint about a high-level gameplay occurrence)
		return {"World.GameplayUpshot"};
	}
	
	virtual TArray<FString> GetCrowdNotifyBaseRemapCategories() const override
	{
		return {"Crowd.GameplayUpshot"};
	}
	
	virtual TArray<FString> GetAgentNotifyBaseRemapCategories() const override
	{
		return {"Agent.GameplayUpshot"};
	}
	//~ End IWorkerUpstreamNotifyGameplayConcept
};

class FWorkerGameplayUpshotEditorModule : public IModuleInterface, public IWorkerGameplayUpshotGameplayConcept
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};