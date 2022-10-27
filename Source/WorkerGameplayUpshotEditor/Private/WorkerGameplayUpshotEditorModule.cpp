// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#include "WorkerGameplayUpshotEditorModule.h"
#include "GameplayTagsEditorModule.h"
#include "WorkerGameplayUpshot.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FWorkerGameplayUpshotEditorModule, WorkerGameplayUpshotEditor);

void FWorkerGameplayUpshotEditorModule::StartupModule()
{
	ApplyGameplayConcept();
	
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	PropertyEditorModule.RegisterCustomPropertyTypeLayout(FWorldGameplayUpshotTag::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGameplayTagCustomizationPublic::MakeInstance));
	PropertyEditorModule.RegisterCustomPropertyTypeLayout(FCrowdGameplayUpshotTag::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGameplayTagCustomizationPublic::MakeInstance));
	PropertyEditorModule.RegisterCustomPropertyTypeLayout(FAgentGameplayUpshotTag::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FGameplayTagCustomizationPublic::MakeInstance));
}

void FWorkerGameplayUpshotEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded(TEXT("PropertyEditor")))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(FWorldGameplayUpshotTag::StaticStruct()->GetFName());
		PropertyModule.UnregisterCustomPropertyTypeLayout(FCrowdGameplayUpshotTag::StaticStruct()->GetFName());
		PropertyModule.UnregisterCustomPropertyTypeLayout(FAgentGameplayUpshotTag::StaticStruct()->GetFName());
	}
}
