/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalRuntimeModule.h"

#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "ReactionalEngine.h"

#define LOCTEXT_NAMESPACE "FReactionalEditorModule"

#pragma optimize("", off)

void FReactionalRuntimeModule::StartupModule()
{
	GETIMELINEHandle = GetGETimelinePluginHandle();
}

void FReactionalRuntimeModule::ShutdownModule() {}

void* FReactionalRuntimeModule::GetGETimelinePluginHandle()
{
	void* Handleptr = nullptr;
#if PLATFORM_WINDOWS
	{
		FString DllPath = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("ReactionalMusic"))->GetBaseDir(), TEXT("/Source/ReactionalThirdPartyLib"));
		FPlatformProcess::PushDllDirectory(*DllPath);
		Handleptr = FPlatformProcess::GetDllHandle(*(DllPath / "ge_timeline.dll"));
		FPlatformProcess::PopDllDirectory(*DllPath);
	}
#endif
    
#if PLATFORM_MAC
	Handleptr = FPlatformProcess::GetDllHandle(TEXT("libge_timeline.dylib"));
#endif
	
#if PLATFORM_ANDROID
	Handleptr = FPlatformProcess::GetDllHandle(TEXT("libge_timeline.so"));
#endif // PLATFORM_ANDROID

	if ( Handleptr == nullptr )
	{
	#if PLATFORM_ANDROID
		UE_LOG(LogAndroid, Log, TEXT("Reactional Handleptr == nullptr"));
	#endif
	}
	else
	{
#if PLATFORM_ANDROID
		UE_LOG(LogAndroid, Log, TEXT("Reactional Handleptr valid"));
#endif
	}

	return Handleptr;
}

DEFINE_LOG_CATEGORY(LogReactionalMusic);

IMPLEMENT_MODULE(FReactionalRuntimeModule, ReactionalRuntime)
#pragma optimize("", on)
#undef LOCTEXT_NAMESPACE