// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#include "WorkerGameplayUpshot.h"
#include "Interfaces/IPluginManager.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, WorkerGameplayUpshot)

DEFINE_LOG_CATEGORY_STATIC(LogWorkerGameplayUpshot, Log, All);

//TArray<FString> FCrowdGameplayUpshotLayoutFragment::GetAvailableGameplayConcepts() const
//{
//	TArray<TSharedRef<IPlugin>> AllPlugins = IPluginManager::Get().GetDiscoveredPlugins();
//	TArray<FString> Result;
//	Result.Reserve(AllPlugins.Num());
//	
//	for (const TSharedRef<IPlugin>& Plugin : AllPlugins)
//	{
//		Result.Add(Plugin->GetName());
//	}
//
//	return Result;
//}

void UWorkerGameplayUpshotStatics::NotifyCrowdActivityWorkerGameplayUpshot(
	TScriptInterface<IGenericAgentActivityWorker> AgentActivityWorker, FAgentGameplayUpshotTag AgentGameplayUpshotTag)
{
	if (!AgentActivityWorker.GetInterface())
	{
		UE_LOG(LogWorkerGameplayUpshot, Error, TEXT("AgentActivityWorker is invalid"));
		return;
	}
	
	if (!AgentGameplayUpshotTag.IsValid())
	{
		UE_LOG(LogWorkerGameplayUpshot, Error, TEXT("AgentGameplayUpshotTag is invalid"));
		return;
	}
		
	UWorkerUpstreamNotifySubsystem::Get()->NotifyCrowdActivityWorker(AgentActivityWorker.GetInterface(), AgentGameplayUpshotTag);
}

void UWorkerGameplayUpshotStatics::NotifyWorldActivityWorkerGameplayUpshot(
	TScriptInterface<IGenericCrowdActivityWorker> CrowdActivityWorker, FCrowdGameplayUpshotTag CrowdGameplayUpshotTag)
{
	if (!CrowdActivityWorker.GetInterface())
	{
		UE_LOG(LogWorkerGameplayUpshot, Error, TEXT("%s failed, CrowdActivityWorker is invalid"), __FUNCTIONW__);
		return;
	}
	
	if (!CrowdGameplayUpshotTag.IsValid())
	{
		UE_LOG(LogWorkerGameplayUpshot, Error, TEXT("%s failed, CrowdGameplayUpshotTag is invalid"), __FUNCTIONW__);
		return;
	}
	
	UWorkerUpstreamNotifySubsystem::Get()->NotifyWorldActivityWorker(CrowdActivityWorker.GetInterface(), CrowdGameplayUpshotTag);
}
