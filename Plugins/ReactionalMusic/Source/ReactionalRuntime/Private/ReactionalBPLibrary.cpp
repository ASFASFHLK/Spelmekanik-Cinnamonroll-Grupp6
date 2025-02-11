/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalBPLibrary.h"

#include "AudioDevice.h"
#include "AudioDeviceManager.h"
#include <limits>
#include "Engine/GameInstance.h"
#include "ReactionalSubsystem.h"

/**
 * ReactionalBPLibrary.cpp
 *
 * This file contains the implementation of the ReactionalBPLibrary class, which provides various utility functions for working with Reactional Music in Unreal Engine.
 * It includes functions for registering with the game instance, setting up asynchronous tasks, reporting success or failure, activating tasks, and handling tick events.
 * It also includes functions for initializing the Reactional Engine, loading data asset bundles, and setting up the Reactional instance manager actor.
 */

#define LOCTEXT_NAMESPACE "ReactionalMusic"
#pragma optimize("", off)

//________________
// Async Task Proxy

UReactionalAsyncTaskBPProxy::UReactionalAsyncTaskBPProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bShouldTick(true)
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		SetFlags(RF_StrongRefOnFrame);
	}
}

void UReactionalAsyncTaskBPProxy::RegisterWithGameInstance(UObject* WorldContextObject)
{
	UWorld* FoundWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (FoundWorld && FoundWorld->GetGameInstance())
	{
		RegisterWithGameInstance(FoundWorld->GetGameInstance());
	}
}

void UReactionalAsyncTaskBPProxy::RegisterWithGameInstance(UGameInstance* GameInstance)
{
	if (GameInstance)
	{
		UGameInstance* OldGameInstance = RegisteredWithGameInstance.Get();
		if (OldGameInstance)
		{
			OldGameInstance->UnregisterReferencedObject(this);
		}

		GameInstance->RegisterReferencedObject(this);
		RegisteredWithGameInstance = GameInstance;
	}
}

void UReactionalAsyncTaskBPProxy::SetReadyToDestroy()
{
	ClearFlags(RF_StrongRefOnFrame);
	if (UGameInstance* OldGameInstance = RegisteredWithGameInstance.Get())
	{
		OldGameInstance->UnregisterReferencedObject(this);
	}
}

void UReactionalAsyncTaskBPProxy::ReportSuccess()
{
	OnSuccess.Broadcast(FString(TEXT("Reactional Success ")) + ReactionalAsyncTaskToStr(AsyncBPTask->TaskType));
}

void UReactionalAsyncTaskBPProxy::ReportFailure()
{
	const char* reactional_error = reactional_string_error(AsyncBPTask->ReturnValueErrorCodeInt);
	FString ErrorString = FString::Printf(TEXT("Reactional ErrorID: %s "), ANSI_TO_TCHAR(reactional_error));

	OnFailed.Broadcast(ErrorString + ReactionalAsyncTaskToStr(AsyncBPTask->TaskType));
}

void UReactionalAsyncTaskBPProxy::Activate()
{
	if (AsyncBPTaskThreadingMode == EReactionalAsyncBPThreadingMode::GameThread_Synchronous)
	{
		AsyncBPTask->Run();
	}
	else
	{
		GIOThreadPool->AddQueuedWork(AsyncBPTask.Get());
	}
}

void UReactionalAsyncTaskBPProxy::Tick(float DeltaTime)
{
	if (!AsyncBPTask.IsValid())
	{
		bShouldTick = false;
		ReportFailure();
		
		//Should be safe here
		SetReadyToDestroy();
		return;
	}

	if (AsyncBPTask->IsDone())
	{
		bShouldTick = false;
		
		// Fire the right delegate
		if (!AsyncBPTask->HadError()) { ReportSuccess(); }
		else						  { ReportFailure(); }
		
		//Should be safe here
		SetReadyToDestroy();
	}
}

//________________
// Setup

UReactionalAsyncTaskBPProxy* UReactionalAsyncTaskBPProxy::Setup_LoadDataAssetBundle(
	UObject* WorldContextObject,
	TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
	EReactionalAsyncBPThreadingMode ThreadingMode
) {
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return nullptr; }
	
	UReactionalAsyncTaskBPProxy* Proxy = NewObject<UReactionalAsyncTaskBPProxy>();
	Proxy->BundleSoftObjectPtr = AssetBundle;
	Proxy->Subsystem = subsystem;

	Proxy->AsyncBPTaskThreadingMode = ThreadingMode;
	Proxy->AsyncBPTaskType = EReactionalAsyncBPTaskType::LoadBundleDataAsset;
	Proxy->AsyncBPTask = MakeShared<FReactionalAsyncBPTask, ESPMode::ThreadSafe>(Proxy->AsyncBPTaskType, Proxy->AsyncBPTaskThreadingMode);
	Proxy->AsyncBPTask->BundleSoftObjectPtr = AssetBundle;
	Proxy->AsyncBPTask->Subsystem = subsystem;

	Proxy->RegisterWithGameInstance(WorldContextObject);
	return Proxy;
}

UReactionalAsyncTaskBPProxy* UReactionalAsyncTaskBPProxy::Setup_LoadDataAssetSection(
	UObject* WorldContextObject,
	TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
	FString SectionName,
	EReactionalAsyncBPThreadingMode ThreadingMode
) {
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return nullptr; }
	
	UReactionalAsyncTaskBPProxy* Proxy = NewObject<UReactionalAsyncTaskBPProxy>();
	Proxy->BundleSoftObjectPtr = AssetBundle;
	Proxy->Subsystem = subsystem;

	Proxy->AsyncBPTaskThreadingMode = ThreadingMode;
	Proxy->AsyncBPTaskType = EReactionalAsyncBPTaskType::LoadSection;
	Proxy->AsyncBPTask = MakeShared<FReactionalAsyncBPTask, ESPMode::ThreadSafe>(Proxy->AsyncBPTaskType, Proxy->AsyncBPTaskThreadingMode);
	Proxy->AsyncBPTask->BundleSoftObjectPtr = AssetBundle;
	Proxy->AsyncBPTask->Subsystem = subsystem;
	Proxy->AsyncBPTask->SectionName = SectionName;

	Proxy->RegisterWithGameInstance(WorldContextObject);
	return Proxy;
}

UReactionalAsyncTaskBPProxy* UReactionalAsyncTaskBPProxy::Setup_LoadDataAssetPlaylist(
	UObject* WorldContextObject,
	TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
	FString	PlaylistName,
	EReactionalAsyncBPThreadingMode ThreadingMode
) {
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return nullptr; }
	
	UReactionalAsyncTaskBPProxy* Proxy = NewObject<UReactionalAsyncTaskBPProxy>();
	Proxy->BundleSoftObjectPtr = AssetBundle;
	Proxy->Subsystem = subsystem;

	Proxy->AsyncBPTaskThreadingMode = ThreadingMode;
	Proxy->AsyncBPTaskType = EReactionalAsyncBPTaskType::LoadPlayList;
	Proxy->AsyncBPTask = MakeShared<FReactionalAsyncBPTask, ESPMode::ThreadSafe>(Proxy->AsyncBPTaskType, Proxy->AsyncBPTaskThreadingMode);
	Proxy->AsyncBPTask->BundleSoftObjectPtr = AssetBundle;
	Proxy->AsyncBPTask->Subsystem = subsystem;
	Proxy->AsyncBPTask->PlaylistName = PlaylistName;

	Proxy->RegisterWithGameInstance(WorldContextObject);
	return Proxy;
}

UReactionalAsyncTaskBPProxy* UReactionalAsyncTaskBPProxy::Setup_LoadDataAssetTrack(
	UObject* WorldContextObject,
	TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
	FString	TrackName,
	EReactionalAsyncBPThreadingMode	ThreadingMode
) {
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return nullptr; }
	
	UReactionalAsyncTaskBPProxy* Proxy = NewObject<UReactionalAsyncTaskBPProxy>();
	Proxy->BundleSoftObjectPtr = AssetBundle;
	Proxy->Subsystem = subsystem;

	Proxy->AsyncBPTaskThreadingMode = ThreadingMode;
	Proxy->AsyncBPTaskType = EReactionalAsyncBPTaskType::LoadTrack;
	Proxy->AsyncBPTask = MakeShared<FReactionalAsyncBPTask, ESPMode::ThreadSafe>(Proxy->AsyncBPTaskType, Proxy->AsyncBPTaskThreadingMode);
	Proxy->AsyncBPTask->BundleSoftObjectPtr = AssetBundle;
	Proxy->AsyncBPTask->Subsystem = subsystem;
	Proxy->AsyncBPTask->TrackName = TrackName;

	Proxy->RegisterWithGameInstance(WorldContextObject);
	return Proxy;
}

UReactionalAsyncTaskBPProxy* UReactionalAsyncTaskBPProxy::Setup_LoadDataAssetTheme(
	UObject* WorldContextObject,
	TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
	FString	ThemeName,
	EReactionalAsyncBPThreadingMode	ThreadingMode
) {
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return nullptr; }
	
	UReactionalAsyncTaskBPProxy* Proxy = NewObject<UReactionalAsyncTaskBPProxy>();
	Proxy->BundleSoftObjectPtr = AssetBundle;
	Proxy->Subsystem = subsystem;

	Proxy->AsyncBPTaskThreadingMode = ThreadingMode;
	Proxy->AsyncBPTaskType = EReactionalAsyncBPTaskType::LoadTheme;
	Proxy->AsyncBPTask = MakeShared<FReactionalAsyncBPTask, ESPMode::ThreadSafe>(Proxy->AsyncBPTaskType, Proxy->AsyncBPTaskThreadingMode);
	Proxy->AsyncBPTask->BundleSoftObjectPtr = AssetBundle;
	Proxy->AsyncBPTask->Subsystem = subsystem;
	Proxy->AsyncBPTask->ThemeName = ThemeName;

	Proxy->RegisterWithGameInstance(WorldContextObject);
	return Proxy;
}

bool UReactionalSetupEngineLibrary::Setup_InitializeReactionalEngine()
{
	UReactionalSubsystem* subsystem = GEngine->GetEngineSubsystem<UReactionalSubsystem>();

	// markus:
	//	Check for previous active engine instance. If plugin modules weakptr to engine instance is valid and there aren't any level InstManagerActors having a valid
	//	created engine instance then assume the engine instance already created is from the editor preview window. In either case we make a shared pointer
	//	to the already created instance and handle the transition accordingly. In the case of editor preview running concurrently we stop the preview playback.
	//	In case of a level Instance ManagerActor (this can happen for example when streaming in a sublevel we handle the transiton by {TODO}
	if(FReactionalEngine::GetEngine())
	{
		//TODO 
		//#WITH_EDITOR CHECK PREVIEW EDITOR
		if (FReactionalEngine::GetEngine() == subsystem->ReactionalEnginePtr.Get())
		{
			REACTIONAL_LOG("Found existing Engine Instance.");
		}
	}
	else
	{
		TSharedRef<FReactionalEngine> EngineInstanceRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();
		if (subsystem->ReactionalEnginePtr.IsValid())
		{
			// markus:
			//	Should never happen
			//	assert(0)
		}
		//This is the "main" engine shared pointer owner.
		subsystem->ReactionalEnginePtr = EngineInstanceRef;
	}

#if PLATFORM_ANDROID
	const char* buildtypestr = reactional_get_build_type();
	UE_LOG(LogAndroid, Log, TEXT("Reactional build type: %s"), ANSI_TO_TCHAR(buildtypestr));
#endif

	auto* Engine = FReactionalEngine::GetEngine();
	//Engine->ReactionalInstActorWeakPtr = InstManagerActor;
	Engine->ReactionalSubsystemWeakPtr = subsystem;

	Engine_InitAudio(-1, -1);

	if (subsystem->EngineProcessThreadingMode == EReactionalThreadingMode::DedicatedThread)
	{
		if (subsystem->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds)
		{
			Engine->EngineThreadingRenderingState = EReactionalEngineThreadingRenderingState::MetasoundRender_DedicatedThreadEventProcessing;
		}
		else if (subsystem->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioSynthComponent)
		{
			Engine->EngineThreadingRenderingState = EReactionalEngineThreadingRenderingState::SynthComponentRender_DedicatedThreadEventProcessing;
		}
		Engine->CreateDedicatedThread();
		Engine->BindStaticDelegates();
		Engine->ReactionalProcessCallTask.Get()->bShouldRun = true;
	}
	else
	{
		if (subsystem->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds)
		{
			Engine->EngineThreadingRenderingState = EReactionalEngineThreadingRenderingState::MetasoundRender_GameThreadEventProcessing;
		}
		else if (subsystem->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioSynthComponent)
		{
			Engine->EngineThreadingRenderingState = EReactionalEngineThreadingRenderingState::SynthComponentRender_GameThreadEventProcessing;
		}
		Engine->StopDedicatedThread();
		Engine->BindStaticDelegates();
	}
	return true;
}

void UReactionalSetupEngineLibrary::Setup_FreeEngineInstance()
{
	if (FReactionalEngine::GetEngine()) { ResetEngine_Impl(true); }
}

void UReactionalSetupEngineLibrary::Setup_RemoveAsset(EReactionalAsset asset_type, const int id)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	auto subsystem = engine->GetSubsystem();
	if(!subsystem) { return; }
	
	int index {};
	switch (asset_type) {
		case Track: { index = subsystem->LoadedTracks.IndexOfByPredicate([&id](const FReactionalTrackInfo& other){ return other.trackID == id; }); break; }
		case Theme: { index = subsystem->LoadedThemes.IndexOfByPredicate([&id](const FReactionalThemeInfo& other){ return other.themeID == id; }); break; }
	}
	if(index == INDEX_NONE)
	{
		REACTIONAL_LOG_WARNING("Could not find %hs with id %d.", to_string(asset_type), id);
		return;
	}
	auto result = reactional_remove_track(lib_ptr, id);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not remove theme with id %d. Reason: %hs", id, error);
	}
	else
	{
		switch (asset_type) {
			case Track: { subsystem->LoadedThemes.RemoveAt(index); break; }
			case Theme: { subsystem->LoadedThemes.RemoveAt(index); break; }
		}
	}
}

//Note that this should only be called from GameThread (BP library is therefore fine)
void UReactionalSetupEngineLibrary::ResetEngine_Impl(bool bFreeEngineInstance)
{
	if (FReactionalEngine::GetEngine())
	{
		UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
		if(!subsystem) { return; }
		
		subsystem->LoadedBundles.Empty();
		subsystem->LoadedThemes.Empty();
		subsystem->LoadedTracks.Empty();
		//subsystem->ParsedSections.Empty();
		//subsystem->ParsedData.Empty();
		subsystem->CurrentSelectedTheme = -1;
		subsystem->CurrentSelectedTrack = -1;

		if (bFreeEngineInstance)
		{
			subsystem->ReactionalEnginePtr = nullptr;
		}
		else
		{
			//A bit unclear what this does
			reactional_reset(FReactionalEngine::GetEngine()->reactionallib_ptr());
		}
	}
}

void UReactionalSetupEngineLibrary::Engine_SetSampleRate(double SampleRate)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 paramId = reactional_find_param(lib_ptr, -1, "sample_rate");
	reactional_set_param_float(lib_ptr, -1, paramId, SampleRate);
}

double UReactionalSetupEngineLibrary::Engine_GetSampleRate()
{
	double Value = std::numeric_limits<double>::min();
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)
	
	int32 paramId = reactional_find_param(lib_ptr, -1, "sample_rate");
	reactional_get_param_float(lib_ptr, -1, paramId, &Value);
	return Value;
}

void UReactionalSetupEngineLibrary::Engine_SetBufferSize(double BufferSize)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 paramId = reactional_find_param(lib_ptr, -1, "block_size");
	reactional_set_param_int(lib_ptr, -1, paramId, BufferSize);
}

int32 UReactionalSetupEngineLibrary::Engine_GetBufferSize()
{
	int64_t Value = std::numeric_limits<int64_t>::min();
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)
	
	int32 paramId = reactional_find_param(lib_ptr, -1, "block_size");
	reactional_get_param_int(lib_ptr, -1, paramId, &Value);
	return Value;
}

void UReactionalSetupEngineLibrary::Engine_InitAudio(int32 SampleRate, int32 BufferSize)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	if (SampleRate < 0) { SampleRate = GetAudioDeviceSampleRateAsInt(); }
	if (BufferSize < 0) { BufferSize = GetAudioDeviceBufferSizeAsInt(); }

	Engine_SetSampleRate(SampleRate);
	Engine_SetBufferSize(BufferSize);
	
	int32 lookahead = reactional_find_param(lib_ptr, -1, TCHAR_TO_ANSI(TEXT("lookahead")));
	int32 lookaheadValue = subsystem->lookaheadMilliseconds * 1000;
	reactional_set_param_int(lib_ptr, -1, lookahead, lookaheadValue);
}

int32 UReactionalSetupEngineLibrary::GetAudioDeviceSampleRateAsInt()
{
	if (FAudioDeviceManager* AudioDeviceManager = FAudioDeviceManager::Get())
	{
		if (FAudioDeviceHandle AudioDeviceHandle = AudioDeviceManager->GetMainAudioDeviceHandle())
		{
			const int32 SampleRate = static_cast<int32>(AudioDeviceHandle->GetSampleRate());
			return SampleRate;
		}
	}
	
	// Fallback sample rate if unable to retrieve from the engine
	REACTIONAL_LOG_WARNING("Failed to get device samplerate, defaulting to 48000.");
	return 48000;
}

int32 UReactionalSetupEngineLibrary::GetAudioDeviceBufferSizeAsInt()
{
	if (FAudioDeviceManager* AudioDeviceManager = FAudioDeviceManager::Get())
	{
		if (FAudioDeviceHandle AudioDeviceHandle = AudioDeviceManager->GetMainAudioDeviceHandle())
		{
			// Assuming GetBufferLength is the method to get the audio buffer size
			const int32 BufferSize = AudioDeviceHandle->GetBufferLength();
			return BufferSize;
		}
	}

	// Fallback buffer size if unable to retrieve from the engine
	REACTIONAL_LOG_WARNING("Failed to get device buffer size, defaulting to 1024.");
	return 1024; // A typical default value, but check what's reasonable in your context
}

void UReactionalSetupEngineLibrary::Engine_SetAllowPlay(bool bAllowPlay)
{
	//can probably be memory order relaxed?
	FReactionalEngine::GetEngine()->_allowPlay.store(bAllowPlay, std::memory_order_seq_cst);
}

bool UReactionalSetupEngineLibrary::Engine_GetAllowPlay()
{
	//can probably be memory order relaxed?
	return FReactionalEngine::GetEngine()->_allowPlay.load(std::memory_order_seq_cst);
}

//________________
// Theme

int32 UReactionalPlaybackLibrary::Theme_GetID()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(false)
	return reactional_get_theme(lib_ptr);
}

bool UReactionalPlaybackLibrary::Theme_GetCurrentThemeInfo(FReactionalThemeInfo& OutThemeInfo)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return false; }
	
	int32 ThemeID = Theme_GetID();
	const FReactionalThemeInfo* FoundThemeInfo = subsystem->LoadedThemes
		.FindByPredicate([&ThemeID](const auto& ThemeInfo) { return ThemeInfo.themeID == ThemeID; });

	if (FoundThemeInfo)
	{
		OutThemeInfo = *FoundThemeInfo;
		return true;
	}
	REACTIONAL_LOG_WARNING("Did not find requested theme in loaded theme.")
	return false;
}

bool UReactionalPlaybackLibrary::Theme_IsLoaded()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(false)
	return reactional_get_theme(lib_ptr) >= 0;
}

void UReactionalPlaybackLibrary::Theme_Play()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()

	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if (subsystem == nullptr || subsystem->LoadedThemes.IsEmpty())
	{
		REACTIONAL_LOG_WARNING("No loaded themes found.")
		return;
	}
	
	int32 themeID = reactional_get_theme(lib_ptr);
	if (themeID < 0)
	{
		int32 autoPlayThemeID = subsystem->LoadedThemes[0].themeID;
		if (reactional_set_theme(lib_ptr, autoPlayThemeID) != 0)
		{
			auto error = reactional_string_error(autoPlayThemeID);
			REACTIONAL_LOG_WARNING("Failed to set theme. ErrorID: %hs", error)
			return;
		}
		themeID = autoPlayThemeID;
		subsystem->CurrentSelectedTheme = 0;
	}
	int32 trackID = reactional_get_track(lib_ptr);
	if (trackID >= 0)
	{
		Playlist_CopyPrerollToTheme(trackID);
	}

	int32 statusParameter = reactional_find_param(lib_ptr, themeID, "status");
	reactional_set_param_int(lib_ptr, themeID, statusParameter, 1);
}

void UReactionalPlaybackLibrary::Theme_SetTheme(const int id)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	auto result = reactional_set_theme(lib_ptr, id);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not set theme with id %d. Reason: %hs", id, error);
	}
}

void UReactionalPlaybackLibrary::Theme_UnsetTheme()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	auto result = reactional_unset_theme(lib_ptr);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not unset theme. Reason: %hs", error);
	}
}

int UReactionalPlaybackLibrary::Theme_GetTheme()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	auto result = reactional_get_theme(lib_ptr);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not get current theme. Reason: %hs", error);
		return -1;
	}
	return result;
}

void UReactionalPlaybackLibrary::Theme_Reset()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 themeID = reactional_get_theme(lib_ptr);
	if (themeID < 0)
	{
		auto error = reactional_string_error(themeID);
		REACTIONAL_LOG_ERROR("Failed to get theme. ErrorID: %hs", error)
		return;
	}
	
	reactional_reset_track(lib_ptr, themeID);
}

void UReactionalPlaybackLibrary::Theme_Stop()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 themeID = reactional_get_theme(lib_ptr);
	if (themeID < 0)
	{
		auto error = reactional_string_error(themeID);
		REACTIONAL_LOG_ERROR("Failed to get theme. ErrorID: %hs", error)
		return;
	}
	//Theme_SetControl("part: silence", 0.f);
	
	int32 statusParameter = reactional_find_param(lib_ptr, themeID, "status");
	reactional_set_param_int(lib_ptr, themeID, statusParameter, 0);
}

void UReactionalPlaybackLibrary::Theme_Fade(
	const float	Target,
	const float	FadeTime,
	const float	Offset,
	const bool bStopFinish
) {
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	auto result = reactional_theme_fade(lib_ptr, Target, Offset, FadeTime * 1'000'000, bStopFinish);
	if(result != 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_WARNING("Failed to fade theme. ErrorID: %hs", error)
	}
}

void UReactionalPlaybackLibrary::Playlist_Fade(
	const float	Target,
	const float	FadeTime,
	const float	Offset,
	const bool bStopFinish
) {
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	auto result = reactional_track_fade(lib_ptr, Target, Offset, FadeTime * 1'000'000, bStopFinish);
	if(result != 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_WARNING("Failed to fade track. ErrorID: %hs", error)
	}
}

int32 UReactionalPlaybackLibrary::Theme_State()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(0)
	
	int32 themeID = reactional_get_theme(lib_ptr);
	if (themeID < 0)
	{
		auto error = reactional_string_error(themeID);
		REACTIONAL_LOG_WARNING("Failed to get theme. ErrorID: %hs", error)
		return 0;
	}

	int32 statusParameter = reactional_find_param(lib_ptr, themeID, "status");
	int64_t Value = std::numeric_limits<int64_t>::min();
	reactional_get_param_int(lib_ptr, themeID, statusParameter, &Value);
	return StaticCast<int32>(Value);
}

void UReactionalPlaybackLibrary::Theme_InstrumentOverride(FString InstrumentName, float PulseRate, float Pitch, float Velocity, bool Active, float Legato)
{
	if(!Theme_IsLoaded()) { return; }

	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 themeID = reactional_get_theme(lib_ptr);
	if (themeID < 0)
	{
		auto error = reactional_string_error(themeID);
		REACTIONAL_LOG_ERROR("Failed to get theme. ErrorID: %hs", error)
		return;
	}
	
	FString ControlName = "Playable Performer: " + InstrumentName;
	int32 controlID = reactional_find_control(lib_ptr, themeID, TCHAR_TO_ANSI(*ControlName));
	if (controlID < 0)
	{
		auto error = reactional_string_error(controlID);
		REACTIONAL_LOG_ERROR("Failed to find control. ErrorID: %hs", error)
		return;
	}
	
	const double values[5] = { (Active ? 1.0 : 0.0), PulseRate, Pitch, Velocity, Legato};
	reactional_set_control_value_array(lib_ptr, themeID, controlID, values, 5);
}

void UReactionalPlaybackLibrary::Theme_GetOverridableInstruments(TArray<FString> &Out)
{
	if(!Theme_IsLoaded()) { return; }
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN()

	int32 themeId = reactional_get_theme(lib_ptr);
	if (themeId < 0)
	{
		auto error = reactional_string_error(themeId);
		REACTIONAL_LOG_ERROR("Failed to get theme. ErrorID: %hs", error)
		return;
	}
	for (int32 i = 0; i < reactional_get_num_controls(lib_ptr, themeId); i++)
	{
		FString ControlName = reactional_get_control_name(lib_ptr, themeId, i);
		if (ControlName.StartsWith("Playable Performer: "))
		{
			Out.Add(ControlName.Mid(20));
		}
	}
}

void UReactionalPlaybackLibrary::Theme_TriggerStinger_Quant(FString	StingerName, EReactionalQuantizationValue Quant)
{
	const float QuantValue = QuantToDouble(Quant);
	const float Value = (QuantValue > 0)
		? QuantValue
		: 0.f;
	Theme_SetControl(StingerName, Value);
}

void UReactionalPlaybackLibrary::Theme_TriggerStinger_Float(FString	StingerName, float Value)
{
	Theme_SetControl(StingerName, Value);
}

void UReactionalPlaybackLibrary::Theme_TriggerState(FString StateName)
{
	SetControl_Impl(StateName, 1.0f, true);
}

void UReactionalPlaybackLibrary::Theme_GetControls(TMap<FString, FReactionalControlInfo> &Out)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	if(!Theme_IsLoaded()) { return; }
	
    int32 themeId = reactional_get_theme(lib_ptr);
    if (themeId >= 0)
    {
        for (int32 i = 0; i < reactional_get_num_controls(lib_ptr, themeId); i++)
        {
            FString controlName = reactional_get_control_name(lib_ptr, themeId, i);
            float controlValue = reactional_get_control_value(lib_ptr, themeId, i);
            FString controlType = reactional_get_control_type(lib_ptr, themeId, i);

        	// super cool hack
        	if(controlType.Equals("parameter")) { controlType = FString("macro"); }
        	
			FReactionalControlInfo controlInfo;
            controlInfo.CurrentValue = controlValue;
            controlInfo.ControlTypeStr = controlType;

            Out.Add(controlName, controlInfo);
        }
    }
	else
	{
		auto error = reactional_string_error(themeId);
		REACTIONAL_LOG_ERROR("Failed to get theme. ErrorID: %hs", error)
	}
}

void UReactionalPlaybackLibrary::Theme_SetControl(FString ControlName, float Value)
{
	Value = FMath::Clamp(Value, 0.f, 1.f);
	SetControl_Impl(ControlName, Value, true);
}

double UReactionalPlaybackLibrary::Theme_GetControl(const FString& InControlName)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(0.f)
	
    int32 themeId = reactional_get_theme(lib_ptr);
    if (themeId >= 0)
    {
        for (int32 i = 0; i < reactional_get_num_controls(lib_ptr, themeId); i++)
        {
            FString controlName = reactional_get_control_name(lib_ptr, themeId, i);
        	if (!controlName.Equals(InControlName)) { continue; }
        	
            return reactional_get_control_value(lib_ptr, themeId, i);
        }
    }
	auto error = reactional_string_error(themeId);
	REACTIONAL_LOG_ERROR("ControlName '%s' was not found. ErrorID: %hs", *InControlName, error)
	return 0.f;
}

float UReactionalPlaybackLibrary::Theme_GetCurrentBeat()
{
	double Value { -1.f };
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)

	int32 themeId = reactional_get_theme(lib_ptr);
	if(themeId < 0)
	{
		auto error = reactional_string_error(themeId);
		REACTIONAL_LOG_WARNING("Failed getting theme. Ensure one is loaded and playback has started. ErrorID: %hs", error)
		return Value;
	}
	auto paramIdx = reactional_find_param(lib_ptr, themeId, "current_beat");
	if(paramIdx < 0)
	{
		auto error = reactional_string_error(paramIdx);
		REACTIONAL_LOG_WARNING("Failed getting current beat parameter index. ErrorID: %hs", error)
	}
	auto result = reactional_get_param_float(lib_ptr, themeId, paramIdx, &Value);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_WARNING("Failed getting current beat. ErrorID: %hs", error)
	}
	return Value / 1'000'000.f;
}

float UReactionalPlaybackLibrary::Theme_GetBPM()
{
	double Value { -1.f };
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)

	int32 themeId = reactional_get_theme(lib_ptr);
	int32 paramIdx = reactional_find_param(lib_ptr, themeId, "bpm");
	if(paramIdx < 0)
	{
		auto error = reactional_string_error(Value);
		REACTIONAL_LOG_WARNING("Failed getting BPM parameter index. ErrorID: %hs", error)
		return Value;
	}
	auto result = reactional_get_param_float(lib_ptr, themeId, paramIdx, &Value);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_WARNING("Failed getting BPM. ErrorID: %hs", error)
	}
	return Value;
}

void UReactionalPlaybackLibrary::Theme_SetVolume(float Value)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()

	Value = FMath::Clamp(Value, std::numeric_limits<double>::min(), 1.f);
	
	int32 ParamID = reactional_find_param(lib_ptr, -1, "theme_gain");
	reactional_set_param_float(lib_ptr, -1, ParamID, Value);
}

float UReactionalPlaybackLibrary::Theme_GetVolume()
{
	double Value = std::numeric_limits<double>::min();
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)
	
	int32 ParamId = reactional_find_param(lib_ptr, -1, "theme_gain");
	reactional_get_param_float(lib_ptr, -1, ParamId, &Value);
	return Value;
}

//________________
// Playlist

int32 UReactionalPlaybackLibrary::Playlist_GetTrackID()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	return reactional_get_track(lib_ptr);
}

FString UReactionalPlaybackLibrary::Playlist_GetCurrentTrackMetadata()
{
	int32 trackID = Playlist_GetTrackID();
	if (trackID < 0) { return FString(TEXT("")); }

	bool bValidRetVal { false };
	FString Result = UReactionalBPLibrary::GetParameterAsString(trackID, FString(TEXT("metadata")), bValidRetVal);
	if (!bValidRetVal) { return FString(TEXT("")); }
	
	return Result;
}

bool UReactionalPlaybackLibrary::Playlist_GetCurrentTrackInfo(FReactionalTrackInfo &OutTrackInfo)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return false; }
	
	int32 TrackID = Playlist_GetTrackID();

	if (const FReactionalTrackInfo* FoundTrackInfo = subsystem->LoadedTracks
			.FindByPredicate([&TrackID](const auto& TrackInfo) { return TrackInfo.trackID == TrackID; })
	) {
		OutTrackInfo = *FoundTrackInfo;
		return true;
	}
	//REACTIONAL_LOG_WARNING("Did not find requested track in loaded tracks.")
	return false;
}

int32 UReactionalPlaybackLibrary::Playlist_GetSelectedTrackIndex()
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return -1; }
	return subsystem->CurrentSelectedTrack;
}

void UReactionalPlaybackLibrary::Playlist_PlayTrackByTrackInfo(const FReactionalTrackInfo &TrackInfo, float FadeOutTime, float FadeInTime)
{
	Playlist_PlayTrackByID_Impl(TrackInfo.trackID, FadeOutTime, FadeInTime);
}

void UReactionalPlaybackLibrary::Playlist_PlayTrackByName(FString TrackName, float FadeOutTime, float FadeInTime)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	const FReactionalTrackInfo* FoundTrackInfo = subsystem->LoadedTracks
		.FindByPredicate([&TrackName](const auto& TrackInfo) { return TrackInfo.trackName.Equals(TrackName); });
	
	if (!FoundTrackInfo)
	{
		REACTIONAL_LOG_ERROR("Track with name %s was not found in loaded tracks.", *TrackName)
		return;
	}
	if (FoundTrackInfo->trackID >= 0)
	{
		Playlist_PlayTrackByID_Impl(FoundTrackInfo->trackID, FadeInTime, FadeOutTime);
	}
}

void UReactionalPlaybackLibrary::Playlist_PlayTrackByIndex(int32 TrackIndex, float FadeOutTime, float FadeInTime)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	// check if index is valid
	if (TrackIndex < 0 || TrackIndex >= subsystem->LoadedTracks.Num())
	{
		REACTIONAL_LOG_ERROR("Index %d was out of bounds for loaded tracks.", TrackIndex)
		return;
	}
	
	FReactionalTrackInfo TrackInfo = subsystem->LoadedTracks[TrackIndex];
	Playlist_PlayTrackByID_Impl(TrackInfo.trackID, FadeOutTime, FadeInTime);
}

void UReactionalPlaybackLibrary::Playlist_PlayTrackByID_Impl(int32 TrackID, float FadeOutTime, float FadeInTime)
{
	if (Playlist_State() == 1)
	{
		//Playlist_Stop(FadeOutTime);
		if(FadeOutTime > 0.f)
		{
			Playlist_Fade(0, FadeOutTime);
		}
		// Set a timer to continue after fadeout completes
		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([=](float) {
			ContinuePlayback(TrackID, FadeInTime);
			return false;
		}), FadeOutTime);
    }
    else
    {
        ContinuePlayback(TrackID, FadeInTime);
    }
}

void UReactionalPlaybackLibrary::ContinuePlayback(int32 TrackID, float FadeInTime)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }

	// Reset track
    reactional_reset_track(lib_ptr, TrackID);
    reactional_set_track(lib_ptr, TrackID);

	subsystem->CurrentSelectedTrack = subsystem->LoadedTracks
		.IndexOfByPredicate([&TrackID](const auto& x) -> int32 { return x.trackID == TrackID; });

	// Reset theme
	int ThemeId = reactional_get_theme(lib_ptr);
    reactional_reset_track(lib_ptr, ThemeId);
    reactional_set_theme(lib_ptr, ThemeId);
    Playlist_CopyPrerollToTheme(TrackID);

	//
	int32 statusParameter = reactional_find_param(lib_ptr, TrackID, "status");
	reactional_set_param_int(lib_ptr, TrackID, statusParameter, 1);
	//
    Theme_Play();
	
	if(FadeInTime > 0.f)
	{
		// Set amplitude to 0
		Playlist_Fade(0, 0, 0);
		// Start fade in after 100ms, does not work if we don't wait
		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([=](float) {
			Playlist_Fade(subsystem->CurrentlySetTrackVolume, FadeInTime);
			return false;
		}), 0.1f);
	}
	int32 ParamId = reactional_find_param(lib_ptr, TrackID, "resample_quality");
	reactional_set_param_int(lib_ptr, TrackID, ParamId, 2);
}

void UReactionalPlaybackLibrary::Playlist_CopyPrerollToTheme(int32 TrackId)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 prerollParamId = reactional_find_param(lib_ptr, TrackId, "pre_roll");
	int64_t Value = std::numeric_limits<int64_t>::min();
	
	bool bParameterValid = (reactional_get_param_int(lib_ptr, TrackId, prerollParamId, &Value) == 0);
	int32 themeID = reactional_get_theme(lib_ptr);
	if (themeID >= 0 && bParameterValid)
	{
		reactional_set_param_int(lib_ptr, themeID, prerollParamId, Value);
	}
}

void UReactionalPlaybackLibrary::Playlist_SetTrack(int id)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	auto result = reactional_set_track(lib_ptr, id);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not set track with id %d. Reason: %hs", id, error);
	}
}

void UReactionalPlaybackLibrary::Playlist_UnsetTrack()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	auto result = reactional_unset_track(lib_ptr);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not unset track. Reason: %hs", error);
	}
}

int UReactionalPlaybackLibrary::Playlist_GetTrack()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	auto result = reactional_get_track(lib_ptr);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not get current track. Reason: %hs", error);
		return -1;
	}
	return result;
}

int UReactionalPlaybackLibrary::Playlist_GetNumTracks()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	auto result = reactional_get_num_tracks(lib_ptr);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_ERROR("Could not get number of tracks. Reason: %hs", error);
		return -1;
	}
	return result;
}

// private async static Task LoadStreamedTrack(TrackInfo ti)
bool UReactionalPlaybackLibrary::Playlist_IsLoaded()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(false)
	return reactional_get_track(lib_ptr) >= 0;
}

void UReactionalPlaybackLibrary::Playlist_Next(float FadeOutTime, float FadeInTime)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	if(subsystem->LoadedTracks.IsEmpty())
	{
		REACTIONAL_LOG_WARNING("No tracks loaded.")
		return;
	}
	int32 trackIndex = (Playlist_GetSelectedTrackIndex() + 1) % subsystem->LoadedTracks.Num();
	if (trackIndex < 0 || trackIndex > subsystem->LoadedTracks.Num() - 1)
	{
		REACTIONAL_LOG_WARNING("Index %d was out of bounds for loaded tracks.", trackIndex)
		return;
	}
	Playlist_PlayTrackByIndex(trackIndex, FadeOutTime, FadeInTime);
}

void UReactionalPlaybackLibrary::Playlist_Prev(float FadeOutTime, float FadeInTime)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	int32 trackIndex = Playlist_GetSelectedTrackIndex() - 1;
	if (trackIndex < 0)
	{
		trackIndex = subsystem->LoadedTracks.Num() - 1;
	}
	Playlist_PlayTrackByIndex(trackIndex, FadeOutTime, FadeInTime);
}

void UReactionalPlaybackLibrary::Playlist_Random(float FadeOutTime, float FadeInTime)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	int32 NumberLoadedTracks = subsystem->LoadedTracks.Num();
	if (NumberLoadedTracks <= 0) { return; }
	
	if (NumberLoadedTracks == 1)
	{
		if (subsystem->CurrentSelectedTrack == 0) { return; }
		
		Playlist_PlayTrackByIndex(0, FadeOutTime, FadeInTime);
		return;
	}
	
	int32 currentTrackIndex = Playlist_GetSelectedTrackIndex();
	int32 trackIndex = FMath::RandRange(0, NumberLoadedTracks - 1);
	while (trackIndex == currentTrackIndex)
	{
		trackIndex = FMath::RandRange(0, NumberLoadedTracks - 1);
	}
	Playlist_PlayTrackByIndex(trackIndex, FadeOutTime, FadeInTime);
}

void UReactionalPlaybackLibrary::Playlist_Stop(float FadeOutTime)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 trackID = reactional_get_track(lib_ptr);
	if (trackID < 0 || Playlist_State() == 0) { return; }
	
	reactional_track_fade(lib_ptr, 0, 0, ((long)FadeOutTime * 1'000'000), true); 
}

void UReactionalPlaybackLibrary::Playlist_Play(float FadeInTime)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }

	if(subsystem->LoadedTracks.IsEmpty())
	{
		REACTIONAL_LOG_WARNING("No tracks loaded.")
		return;
	}
	
	int32 trackID = reactional_get_track(lib_ptr);
	if (trackID < 0)
	{
		int32 autoPlayTrackID = subsystem->LoadedTracks[0].trackID;
		if (reactional_set_track(lib_ptr, autoPlayTrackID) != 0) { return; }
		trackID = autoPlayTrackID;
	}
	
	if (trackID >= 0)
	{
		Playlist_PlayTrackByID_Impl(trackID, 0, FadeInTime);
	}
}

int32 UReactionalPlaybackLibrary::Playlist_State()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	
	int32 trackID = reactional_get_track(lib_ptr);
	if (trackID < 0)
	{
		//auto error = reactional_string_error(trackID);
		//REACTIONAL_LOG_ERROR("Failed to get track. ErrorID: %hs", error)
		return 0;
	}

	int32 statusParameter = reactional_find_param(lib_ptr, trackID, "status");
	int64_t Value = std::numeric_limits<int64_t>::min();
	reactional_get_param_int(lib_ptr, trackID, statusParameter, &Value);
	return StaticCast<int32>(Value);
}

float UReactionalPlaybackLibrary::Playlist_GetCurrentBeat()
{
	double Value { -1.f };
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)

	int32 trackId = reactional_get_track(lib_ptr);
	if(trackId < 0)
	{
		auto error = reactional_string_error(trackId);
		REACTIONAL_LOG_WARNING("Failed getting track. Ensure one is loaded and playback has started. ErrorID: %hs", error)
		return Value;
	}
	auto paramIdx = reactional_find_param(lib_ptr, trackId, "current_beat");
	if(paramIdx < 0)
	{
		auto error = reactional_string_error(paramIdx);
		REACTIONAL_LOG_WARNING("Failed getting current beat parameter index. ErrorID: %hs", error)
	}
	auto result = reactional_get_param_float(lib_ptr, trackId, paramIdx, &Value);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_WARNING("Failed getting current beat parameter. ErrorID: %hs", error)
	}
	return Value / 1'000'000.f;
}

float UReactionalPlaybackLibrary::Playlist_GetBPM()
{
	double Value { -1.f };
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)

	int32 trackId = reactional_get_track(lib_ptr);
	if(trackId < 0)
	{
		auto error = reactional_string_error(trackId);
		REACTIONAL_LOG_WARNING("Failed getting track. Ensure one is loaded and playback has started. ErrorID: %hs", error)
		return Value;
	}
	int32 paramIdx = reactional_find_param(lib_ptr, trackId, "bpm");
	if(paramIdx < 0)
	{
		auto error = reactional_string_error(paramIdx);
		REACTIONAL_LOG_WARNING("Failed getting BPM parameter. ErrorID: %hs", error)
		return Value;
	}
	auto result = reactional_get_param_float(lib_ptr, trackId, paramIdx, &Value);
	if(result < 0)
	{
		auto error = reactional_string_error(result);
		REACTIONAL_LOG_WARNING("Failed getting BPM. ErrorID: %hs", error)
	}
	return Value;
}

void UReactionalPlaybackLibrary::Playlist_SetVolume(float Value)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	Value = FMath::Clamp(Value, 0.f, 1.f);

	auto ParamId = reactional_find_param(lib_ptr, -1, "track_gain");
	reactional_set_param_float(lib_ptr, -1, ParamId, Value);
}

float UReactionalPlaybackLibrary::Playlist_GetVolume()
{
	double Value = std::numeric_limits<double>::min();
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN(Value)
	
	int32 ParamId = reactional_find_param(lib_ptr, -1, "track_gain");
	reactional_get_param_float(lib_ptr, -1, ParamId, &Value);
	return Value;
}

//________________
// Music System

void UReactionalPlaybackLibrary::MusicSystem_ScheduleAudio(USoundBase* Sound, float Quant, float TimeOffset)
{
	if(!Theme_IsLoaded() && !Playlist_IsLoaded()) { return; }
	
	float TimeToBeat = MusicSystem_GetTimeToBeat(Quant, TimeOffset);
	if (TimeToBeat < 0)
	{
		auto error = reactional_string_error(TimeToBeat);
		REACTIONAL_LOG_WARNING("Failed to get time to beat. Ensure engine is initialized and that playback has started. ErrorID: %hs", error)
		return;
	}
	
	// gin:
	//	creating a new audio component to enable any number of playbacks.
	//	investigate if we want a settable concurrency variable to set a max amount of scheduled sounds, doable with an owner.
	//	bAutoDestroy is enabled by default so the component and sound should be freed once used.
	
	FAudioDevice::FCreateComponentParams Params = FAudioDevice::FCreateComponentParams(GEngine->GetActiveAudioDevice().GetAudioDevice());
	UAudioComponent* Audio = FAudioDevice::CreateComponent(Sound, Params);
	if (Audio)
	{
		Audio->SetVolumeMultiplier(1);
		Audio->SetPitchMultiplier(1);
		Audio->bAllowSpatialization = false;
		Audio->bIsUISound = true;
		Audio->bAutoDestroy = true;
		Audio->bIgnoreForFlushing = true;
		Audio->SubtitlePriority = Sound->GetSubtitlePriority();
		Audio->bStopWhenOwnerDestroyed = false;
	}
	else REACTIONAL_LOG_ERROR("Failed to create audio component.")

	float QuantBeat = MusicSystem_GetNextBeatAbsolute(Quant) + (TimeOffset * 1'000'000.f);
	float Beat = MusicSystem_GetNextBeat(Quant);

	FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([=](float) {
		REACTIONAL_GET_LIB_PTR_OR_RETURN(false)
		float quantBeat = QuantBeat;
		double mb = MusicSystem_GetCurrentMicroBeat();
		if ((quantBeat - mb) > (Beat + 1)) quantBeat = MusicSystem_GetNextBeatAbsolute(Beat) + (TimeOffset * 1'000'000.f);
		if(mb < quantBeat) { return true; }
		
		if(!Audio || !Audio->IsValidLowLevel()) { return false; }
		Audio->Play();
		return false;
	}));
}

float UReactionalPlaybackLibrary::MusicSystem_GetTimeToBeat(float Quant, float Offset, bool bTheme)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1.f)
	
	int32 themeId = reactional_get_theme(lib_ptr);
	int32 trackId = reactional_get_track(lib_ptr);
	int32 id = (themeId >= 0)
		? themeId
		: trackId;

	long nextQuant = reactional_get_next_quant_beat(lib_ptr, id, Quant * 1'000'000.f, Offset);
	double currBeat = MusicSystem_GetCurrentMicroBeat();

	return (nextQuant - currBeat) / 1'000'000.f;
}

float UReactionalPlaybackLibrary::MusicSystem_GetRealTimeToBeat(float Quant)
{
	float timeToBeat = MusicSystem_GetTimeToBeat(Quant, 0.f);
	float seconds = MusicSystem_BeatsToSeconds(timeToBeat);
	return seconds;
}

float UReactionalPlaybackLibrary::MusicSystem_GetNextBeat(float Quant, float Offset, bool bTheme)
{
	float nextBeat = MusicSystem_GetNextBeatAbsolute(Quant, Offset, bTheme);
	return nextBeat / 1'000'000.f;
}

int64 UReactionalPlaybackLibrary::MusicSystem_GetNextBeatAbsolute(double Quant, float Offset, bool bTheme)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	
	if(!Theme_IsLoaded()) { return -1.0; }
	
	int32 trackID = (bTheme)
		? reactional_get_theme(lib_ptr)
		: reactional_get_track(lib_ptr);
	
	if (trackID < 0)
	{
		auto error = reactional_string_error(trackID);
		REACTIONAL_LOG_ERROR("Failed to set track. ErrorID: %hs", error)
		return -1;
	}
	
	int64 nextQuant = reactional_get_next_quant_beat(lib_ptr, trackID, Quant * 1'000'000.f, Offset * 1'000'000.f);
	return nextQuant;
}

float UReactionalPlaybackLibrary::MusicSystem_GetCurrentBeat()
{
	double microBeat = MusicSystem_GetCurrentMicroBeat();
	return microBeat / 1'000'000.f;
}

double UReactionalPlaybackLibrary::MusicSystem_GetCurrentMicroBeat()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1.0)
	
	if(!Theme_IsLoaded()) { return -1.0; }
	
	int32 themeId = reactional_get_theme(lib_ptr);
	int32 trackId = reactional_get_track(lib_ptr);
	double RetValue = std::numeric_limits<double>::min();

	int32 id = (themeId >= 0)
		? themeId
		: trackId;

	if (id >= 0)
	{
		int32 paramId = reactional_find_param(lib_ptr, id, "current_beat");
		reactional_get_param_float(lib_ptr, id, paramId, &RetValue);
	}
	else
	{
		auto error = reactional_string_error(id);
		REACTIONAL_LOG_ERROR("Failed to set track. ErrorID: %hs", error)
	}
	return RetValue;
}

float UReactionalPlaybackLibrary::MusicSystem_GetBPM()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	
	int32 themeId = reactional_get_theme(lib_ptr);
	double Value = std::numeric_limits<double>::min();
	if (themeId >= 0)
	{
		int32 paramId = reactional_find_param(lib_ptr, themeId, "bpm");
		if(paramId < 0)
		{
			auto error = reactional_string_error(paramId);
			REACTIONAL_LOG_WARNING("Failed getting BPM parameter. ErrorID: %hs", error)
			return Value;
		}
		reactional_get_param_float(lib_ptr, themeId, paramId, &Value);
	}
	return Value;
}

float UReactionalPlaybackLibrary::MusicSystem_BeatsToSeconds(float Beats)
{
	float tempo = MusicSystem_GetBPM();
	return (60.f / tempo) * Beats;
}

void UReactionalPlaybackLibrary::MusicSystem_DuckMusic(float Amp)
{
	auto FadeTime = 0.75f;
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	if (Amp < 1 && !subsystem->bIsDucked)
	{
		subsystem->CurrentlySetTrackVolume = Playlist_GetVolume();
		subsystem->bIsDucked = true;
		Playlist_Fade(Amp, FadeTime);
	}
	else if (Amp == 1 && subsystem->bIsDucked)
	{
		subsystem->bIsDucked = false;
		Playlist_Fade(subsystem->CurrentlySetTrackVolume, FadeTime);
	}
}

void UReactionalPlaybackLibrary::MusicSystem_WaitForNextBeat(
	UObject* WorldContextObject,
	FLatentActionInfo LatentInfo,
	float Beat,
	float Offset
) {
	auto QuantBeat = MusicSystem_GetNextBeatAbsolute(Beat, Offset);
	if(QuantBeat == -1)
	{
		auto error = reactional_string_error(QuantBeat);
		REACTIONAL_LOG_WARNING("Invalid value. Ensure engine is initialized and that playback has started. ErrorID: %hs", error)
		return;
	}
	
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		if (LatentActionManager.FindExistingAction<FWaitForBeatLatentAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FWaitForBeatLatentAction(QuantBeat, Beat, Offset, LatentInfo)
			);
		}
	}
}

void UReactionalPlaybackLibrary::MusicSystem_SubscribeToQuantizationEvent(
	EReactionalQuantizationValue Quant,
	const FReactionalQuantizationEvent& OnQuantizationEvent
) {
	auto subsystem = GEngine->GetEngineSubsystem<UReactionalSubsystem>();
	if(!subsystem) { return; }
	subsystem->QuantizationEvents[static_cast<int>(Quant)].Delegate.AddUnique(OnQuantizationEvent);
}

void UReactionalPlaybackLibrary::SetControl_Impl(const FString& ControlName, float Value, bool bIsTheme)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	if (bIsTheme)
	{
		int32 themeId = reactional_get_theme(lib_ptr);
		int32 controlId = reactional_find_control(lib_ptr, themeId, TCHAR_TO_ANSI(*ControlName));
		if (controlId >= 0)
		{
			reactional_set_control_value(lib_ptr, themeId, controlId, Value);
		}
		else REACTIONAL_LOG_WARNING("Control name '%s' was not found.", *ControlName)
	}
	else
	{
		int32 trackId = reactional_get_track(lib_ptr);
		if (trackId >= 0)
		{
			int32 controlId = reactional_find_control(lib_ptr, trackId, TCHAR_TO_ANSI(*ControlName));
			if (controlId >= 0)
			{
				reactional_set_control_value(lib_ptr, trackId, controlId, Value);
			}
			else REACTIONAL_LOG_WARNING("Control name '%s' was not found.", *ControlName)
		}
	}
}

void UReactionalBPLibrary::PlaylistStart(bool bRandomTrack)
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	if (subsystem->LoadedTracks.Num() > 0)
	{
		REACTIONAL_GET_LIB_PTR_OR_RETURN()
		
		int32 arrayIdx = FMath::RandRange(0, subsystem->LoadedTracks.Num() - 1);
		int32 autoPlayTrackID = bRandomTrack ? subsystem->LoadedTracks[arrayIdx].trackID : 0;
		if (reactional_set_track(lib_ptr, autoPlayTrackID) != 0)
		{
			auto error = reactional_string_error(autoPlayTrackID);
			REACTIONAL_LOG_ERROR("Failed to set track. ErrorID: %hs", error)
			return;
		}

		if (reactional_reset_track(lib_ptr, autoPlayTrackID) != 0)
		{
			auto error = reactional_string_error(autoPlayTrackID);
			REACTIONAL_LOG_ERROR("Failed to reset track. ErrorID: %hs", error)
			return;
		}

		int32 SelectedTheme = subsystem->CurrentSelectedTheme;
		if (SelectedTheme >= 0 && SelectedTheme < subsystem->LoadedThemes.Num())
		{
			ThemeStop();
		}

		int32 SelectedTrack = subsystem->CurrentSelectedTrack;
		if (SelectedTrack >= 0 && SelectedTrack < subsystem->LoadedTracks.Num())
		{
			PlaylistStop();
		}
		
		int32 statusParameter = reactional_find_param(lib_ptr, autoPlayTrackID, "status");
		int32 errorid = reactional_set_param_int(lib_ptr, autoPlayTrackID, statusParameter, 1);
		if (errorid != 0)
		{
			auto error = reactional_string_error(autoPlayTrackID);
			REACTIONAL_LOG_ERROR("Failed to set status parameter. ErrorID: %hs", error)
			return;
		}
		
		subsystem->CurrentSelectedTrack = arrayIdx;
	}
}

void UReactionalBPLibrary::PlaylistStop()
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }

	if (subsystem->LoadedTracks.Num() > 0)
	{
		int32 Idx = subsystem->CurrentSelectedTrack;
		if (Idx < 0 || Idx >= subsystem->LoadedTracks.Num())
		{
			subsystem->CurrentSelectedTrack = -1;
			return;
		}
		REACTIONAL_GET_LIB_PTR_OR_RETURN()

		int32 playingTrackID = subsystem->LoadedTracks[Idx].trackID;

		int32 statusParameter = reactional_find_param(lib_ptr, playingTrackID, "status");
		int32 errorid = reactional_set_param_int(lib_ptr, playingTrackID, statusParameter, 0);
		if (errorid != 0)
		{
			auto error = reactional_string_error(errorid);
			REACTIONAL_LOG_ERROR("Failed to set status parameter. ErrorID: %hs", error)
			return;
		}
		
		subsystem->CurrentSelectedTrack = -1;
	}
}

void UReactionalBPLibrary::PlaylistNext()
{
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }
	
	if (subsystem->LoadedTracks.Num() > 0)
	{
		int32 Idx = subsystem->CurrentSelectedTrack;
		if (Idx < 0 || Idx >= subsystem->LoadedTracks.Num())
		{
			subsystem->CurrentSelectedTrack = -1;
			return;
		}

		int32 nextTrackID = Idx + 1;
		if (nextTrackID >= subsystem->LoadedTracks.Num())
		{
			nextTrackID = 0;
		}
		REACTIONAL_GET_LIB_PTR_OR_RETURN()

		int32 playingTrackID = subsystem->LoadedTracks[Idx].trackID;
		if (reactional_reset_track(lib_ptr, playingTrackID) != 0) { return; }
		
		int32 statusParameter = reactional_find_param(lib_ptr, playingTrackID, "status");
		int32 errorid = reactional_set_param_int(lib_ptr, playingTrackID, statusParameter, 0);
		if (errorid != 0)
		{ 
			auto error = reactional_string_error(errorid);
			REACTIONAL_LOG_ERROR("Failed to set status parameter. ErrorID: %hs", error)
			return;
		}
		
		subsystem->CurrentSelectedTrack = -1;

		int32 nextPlayingTrackID = subsystem->LoadedTracks[nextTrackID].trackID;
		errorid = reactional_reset_track(lib_ptr, nextPlayingTrackID);
		if (errorid != 0)
		{
			auto error = reactional_string_error(errorid);
			REACTIONAL_LOG_ERROR("Failed to reset track. ErrorID: %hs", error)
			return;
		}

		errorid = reactional_unset_track(lib_ptr);
		if (errorid != 0)
		{
			auto error = reactional_string_error(errorid);
			REACTIONAL_LOG_ERROR("Failed to unset track. ErrorID: %hs", error)
			return;
		}

		errorid = reactional_set_track(lib_ptr, nextPlayingTrackID);
		if (errorid != 0)
		{
			auto error = reactional_string_error(errorid);
			REACTIONAL_LOG_ERROR("Failed to set track. ErrorID: %hs", error)
			return;
		}

		statusParameter = reactional_find_param(lib_ptr, nextPlayingTrackID, "status");
		errorid = reactional_set_param_int(lib_ptr, nextPlayingTrackID, statusParameter, 1);
		if (errorid != 0)
		{
			auto error = reactional_string_error(errorid);
			REACTIONAL_LOG_ERROR("Failed to set status parameter. ErrorID: %hs", error)
			return;
		}

		subsystem->CurrentSelectedTrack = nextTrackID;
	}
}

void UReactionalBPLibrary::ThemeStart()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }

	if (subsystem->LoadedThemes.Num() > 0)
	{
		reactional_unset_track(lib_ptr);
		reactional_unset_theme(lib_ptr);

		int32 autoPlayThemeID = subsystem->LoadedThemes[0].themeID;
		if (reactional_set_theme(lib_ptr, autoPlayThemeID) != 0)
		{
			REACTIONAL_LOG_WARNING("Failed to set theme.")
			return;
		}

		if (reactional_reset_track(lib_ptr, autoPlayThemeID) != 0)
		{
			REACTIONAL_LOG_WARNING("Failed resetting track.")
			return;
		}

		if (subsystem->CurrentSelectedTheme >= 0 && subsystem->CurrentSelectedTheme < subsystem->LoadedThemes.Num())
		{
			ThemeStop();
		}

		if (subsystem->CurrentSelectedTrack >= 0 && subsystem->CurrentSelectedTrack < subsystem->LoadedTracks.Num())
		{
			PlaylistStop();
		}

		int32 statusParameter = reactional_find_param(lib_ptr, autoPlayThemeID, "status");
		int32 errorid = reactional_set_param_int(lib_ptr, autoPlayThemeID, statusParameter, 1);
		if (errorid != 0)
		{
			REACTIONAL_LOG_WARNING("Failed setting status parameter.")
			return;
		}

		subsystem->CurrentSelectedTheme = 0;
	}
}

void UReactionalBPLibrary::ThemeStop()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	UReactionalSubsystem* subsystem = UReactionalSubsystem::GetSubsystem();
	if(!subsystem) { return; }

	if (subsystem->LoadedThemes.Num() > 0)
	{
		int32 Idx = subsystem->CurrentSelectedTheme;

		if (Idx < 0 || Idx >= subsystem->LoadedThemes.Num())
		{
			reactional_unset_theme(lib_ptr);
			subsystem->CurrentSelectedTheme = -1;
			return;
		}

		int32 playingThemeID = subsystem->LoadedThemes[Idx].themeID;

		int32 statusParameter = reactional_find_param(lib_ptr, playingThemeID, "status");
		int32 errorid = reactional_set_param_int(lib_ptr, playingThemeID, statusParameter, 0);
		if (errorid != 0)
		{
			reactional_unset_theme(lib_ptr);
			return;
		}
		
		subsystem->CurrentSelectedTheme = -1;
		reactional_unset_theme(lib_ptr);
	}
}

int64 UReactionalBPLibrary::GetNextQuantBeat(int64 in_quant, int64 in_phase)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)

	int32 themeId = reactional_get_theme(lib_ptr);
	if (themeId >= 0)
	{
		return reactional_get_next_quant_beat(lib_ptr, themeId, in_quant, in_phase);
	}
	
	int32 trackId = reactional_get_track(lib_ptr);
	if (trackId >= 0)
	{
		return reactional_get_next_quant_beat(lib_ptr, trackId, in_quant, in_phase);
	}

	REACTIONAL_LOG_WARNING("Could not query track nor theme. Ensure one is playing.")
	return -1;
}

float UReactionalBPLibrary::GetCurrentBeatAsFloat()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(std::numeric_limits<float>::max())
	
	int32 Id = reactional_get_theme(lib_ptr);
	if (Id < 0)
	{
		Id = reactional_get_track(lib_ptr);
		if (Id < 0)
		{
			return std::numeric_limits<float>::max();
		}
	}

	bool bValidRetVal = false;
	float RetValue = StaticCast<float>(GetParameterAsInt(Id, FString(TEXT("current_beat")), bValidRetVal));
	if (bValidRetVal)
	{
		return RetValue / 1'000'000.0f;
	}

	return std::numeric_limits<float>::max();
}

int32 UReactionalBPLibrary::GetCurrentBeatAsInt()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(std::numeric_limits<float>::max())
	
	int32 Id = reactional_get_theme(lib_ptr);
	if (Id < 0)
	{
		Id = reactional_get_track(lib_ptr);
		if (Id < 0)
		{
			return std::numeric_limits<int32>::max();
		}
	}

	bool bValidRetVal = false;
	int32 RetValue = GetParameterAsInt(Id, FString(TEXT("current_beat")), bValidRetVal);
	if (bValidRetVal)
	{
		return RetValue;
	}

	return std::numeric_limits<int32>::max();
}

double UReactionalBPLibrary::GetCurrentBeatAsDouble()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(std::numeric_limits<float>::max())
	
	int32 Id = reactional_get_theme(lib_ptr);
	if (Id < 0)
	{
		Id = reactional_get_track(lib_ptr);
		if (Id < 0)
		{
			return std::numeric_limits<double>::max();
		}
	}

	bool bValidRetVal = false;
	double RetValue = GetParameterAsInt(Id, FString(TEXT("current_beat")), bValidRetVal);
	if (bValidRetVal)
	{
		return RetValue / 1'000'000.0;
	}

	return std::numeric_limits<double>::max();
}

float UReactionalBPLibrary::GetBPM()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(std::numeric_limits<float>::max())
	
	int32 Id = reactional_get_theme(lib_ptr);
	if (Id <  0)
	{
		Id = reactional_get_track(lib_ptr);
		if (Id < 0)
		{
			return std::numeric_limits<float>::max();
		}
	}

	bool bValidRetVal = false;
	float RetValue = GetParameterAsFloat(Id, FString(TEXT("bpm")), bValidRetVal);
	if (bValidRetVal)
	{
		return RetValue;
	}

	return std::numeric_limits<float>::max();
}

int32 UReactionalBPLibrary::FindControl(int32 trackthemeId, FString ControlName)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)

	if (trackthemeId >= 0)
	{
		int32 controlId = reactional_find_control(lib_ptr, trackthemeId, TCHAR_TO_ANSI(*ControlName));
		return controlId;
	}
	return -1;
}

int32 UReactionalBPLibrary::FindParameter(int32 trackthemeId, FString ParamName)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	
	if (trackthemeId >= 0)
	{
		int32 paramId = reactional_find_param(lib_ptr, trackthemeId, TCHAR_TO_ANSI(*ParamName));
		return paramId;
	}
	return -1;
}

float UReactionalBPLibrary::SetFloatParameter(FString ParamName, float ParamValue, bool &bValid)
{
	bValid = false;
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN(std::numeric_limits<float>::max())

	int32 Id = reactional_get_theme(lib_ptr);
	if (Id < 0)
	{
		Id = reactional_get_track(lib_ptr);
		if (Id < 0)
		{
			return std::numeric_limits<float>::max();
		}
	}

	int32 ParamId = FindParameter(Id, ParamName);
	if (ParamId >= 0)
	{
		int32 CheckParamType = reactional_get_param_type(lib_ptr, Id, ParamId);
		if (CheckParamType >= 0)
		{
			EReactionalParameterType ParamType = EReactionalParameterType((uint8(CheckParamType)));
			if (ParamType == EReactionalParameterType::ParameterType_Float)
			{
				int32 result = reactional_set_param_float(lib_ptr, Id, ParamId, ParamValue);
				if (result == 0)
				{
					bValid = true;
					return ParamValue;
				}
			}
		}
	}
	return std::numeric_limits<float>::max();
}

int32 UReactionalBPLibrary::SetIntParameter(FString ParamName, int32 ParamValue, bool &bValid)
{
	bValid = false;
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN(std::numeric_limits<float>::max())

	int32 Id = reactional_get_theme(lib_ptr);
	if (Id < 0)
	{
		Id = reactional_get_track(lib_ptr);
		if (Id < 0)
		{
			return std::numeric_limits<int32>::max();
		}
	}

	int32 ParamId = FindParameter(Id, ParamName);
	if (ParamId >= 0)
	{
		int32 CheckParamType = reactional_get_param_type(lib_ptr, Id, ParamId);
		if (CheckParamType >= 0)
		{
			EReactionalParameterType ParamType = EReactionalParameterType((uint8(CheckParamType)));
			if (ParamType == EReactionalParameterType::ParameterType_Int)
			{
				int32 result = reactional_set_param_int(lib_ptr, Id, ParamId, ParamValue);
				if (result == 0)
				{
					bValid = true;
					return ParamValue;
				}
			}
		}
	}
	return std::numeric_limits<int32>::max();
}

FString UReactionalBPLibrary::GetParameterAsString(int32 trackthemeId, FString ParamName, bool &bValid)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(FString(TEXT("Failed to get engine")))
	
	int32 ParamId = FindParameter(trackthemeId, ParamName);
	bValid = false;
	if (ParamId >= 0)
	{
		int32 CheckParamType = reactional_get_param_type(lib_ptr, trackthemeId, ParamId);
		if (CheckParamType >= 0)
		{
			EReactionalParameterType ParamType = EReactionalParameterType((uint8(CheckParamType)));
			if (ParamType == EReactionalParameterType::ParameterType_String)
			{
				TArray<char> charBuf;
				charBuf.AddZeroed(512);
				charBuf[511] = '\0';

				int32 result = reactional_get_param_string(lib_ptr, trackthemeId, ParamId, charBuf.GetData(), charBuf.Num()-1);
				if (result > 0)
				{
					FString s = ANSI_TO_TCHAR(charBuf.GetData());
					return s;
				}
			}
		}
	}
	return FString(TEXT("Invalid data"));
}

float UReactionalBPLibrary::GetParameterAsFloat(int32 trackthemeId, FString ParamName, bool &bValid)
{
	bValid = false;

	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1.0f)
	
	int32 ParamId = FindParameter(trackthemeId, ParamName);
	if (ParamId >= 0)
	{
		int32 CheckParamType = reactional_get_param_type(lib_ptr, trackthemeId, ParamId);
		if (CheckParamType >= 0)
		{
			EReactionalParameterType ParamType = EReactionalParameterType((uint8(CheckParamType)));
			if (ParamType == EReactionalParameterType::ParameterType_Float)
			{
				double value = std::numeric_limits<double>::max();
				int32 result = reactional_get_param_float(lib_ptr, trackthemeId, ParamId, &value);
				if (result == 0)
				{
					bValid = true;
					return value;
				}
			}
		}
	}
	return -1.0f;
}

int32 UReactionalBPLibrary::GetParameterAsInt(int32 trackthemeId, FString ParamName, bool &bValid)
{
	bValid = false;
	
	REACTIONAL_GET_LIB_PTR_OR_RETURN(-1)
	
	int32 ParamId = FindParameter(trackthemeId, ParamName);
	if (ParamId >= 0)
	{
		
		int32 CheckParamType = reactional_get_param_type(lib_ptr, trackthemeId, ParamId);
		if (CheckParamType >= 0)
		{
			EReactionalParameterType ParamType = EReactionalParameterType((uint8(CheckParamType)));
			if (ParamType == EReactionalParameterType::ParameterType_Int)
			{
				int64_t value = std::numeric_limits<int64_t>::max();
				int32 result = reactional_get_param_int(lib_ptr, trackthemeId, ParamId, &value);
				if (result == 0)
				{
					bValid = true;
					return value;
				}
			}
		}
	}
	return -1;
}

bool UReactionalBPLibrary::GetParameterAsBool(int32 trackthemeId, FString ParamName, bool &bValid)
{
	bValid = false;

	REACTIONAL_GET_LIB_PTR_OR_RETURN(false)
	
	int32 ParamId = FindParameter(trackthemeId, ParamName);
	if (ParamId >= 0)
	{
		
		int32 CheckParamType = reactional_get_param_type(lib_ptr, trackthemeId, ParamId);
		if (CheckParamType >= 0)
		{
			EReactionalParameterType ParamType = EReactionalParameterType((uint8(CheckParamType)));
			if (ParamType == EReactionalParameterType::ParameterType_Bool)
			{
				bool value = false;
				int32 result = reactional_get_param_bool(lib_ptr, trackthemeId, ParamId, &value);
				if (result == 0)
				{
					bValid = true;
					return value;
				}
			}
		}
	}
	return false;
}

float UReactionalBPLibrary::GetControlValue(FString ControlName)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(std::numeric_limits<float>::max())
	
	int32 themeId = reactional_get_theme(lib_ptr);
	if (themeId >= 0)
	{
		int32 controlId = reactional_find_control(lib_ptr, themeId, TCHAR_TO_ANSI(*ControlName));
		if (controlId >= 0)
		{
			return (float)reactional_get_control_value(lib_ptr, themeId, controlId);
		}
	}
	else
	{
		int32 trackId = reactional_get_track(lib_ptr);
		if (trackId >= 0)
		{
			int32 controlId = reactional_find_control(lib_ptr, trackId, TCHAR_TO_ANSI(*ControlName));
			if (controlId >= 0)
			{
				return (float)reactional_get_control_value(lib_ptr, trackId, controlId);
			}
		}
	}
	return std::numeric_limits<float>::max();
}

void UReactionalBPLibrary::SetControlValue(FString ControlName, float ControlValue)
{
	if (ControlValue < 0.f || ControlValue > 1.f)
	{
		REACTIONAL_LOG_WARNING("Invalid ControlValue parameter passed. Value needs to be normalized between 0 and 1.")
		return;
	}

	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 themeId = reactional_get_theme(lib_ptr);
	if (themeId >= 0)
	{
		int32 controlId = reactional_find_control(lib_ptr, themeId, TCHAR_TO_ANSI(*ControlName));
		if (controlId >= 0)
		{
			reactional_set_control_value(lib_ptr, themeId, controlId, ControlValue);
		}
	}
	else
	{
		int32 trackId = reactional_get_track(lib_ptr);
		if (trackId >= 0)
		{
			int32 controlId = reactional_find_control(lib_ptr, trackId, TCHAR_TO_ANSI(*ControlName));
			if (controlId >= 0)
			{
				reactional_set_control_value(lib_ptr, trackId, controlId, ControlValue);
			}
		}
	}
}

void UReactionalBPLibrary::GetControlNames(bool bIsTheme, TArray<FString> &ControlNames)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	
	int32 trackId = bIsTheme
		? reactional_get_theme(lib_ptr)
		: reactional_get_track(lib_ptr);
	
	if ( trackId >= 0)
	{
		int32 nbrOfControls = reactional_get_num_controls(lib_ptr, trackId);
		for (int32 i = 0; i < nbrOfControls; i++)
		{
			const char* stringchar = reactional_get_control_name(lib_ptr, trackId, i);
			FString strName(ANSI_TO_TCHAR(stringchar));
			if (!strName.IsEmpty() && !strName.StartsWith(TEXT("t_")))
			{
				ControlNames.Add(strName);
			}
		}
	}
}

void UReactionalBPLibrary::GetParameterNames(bool bIsTheme, TArray<FString> &ParameterNames)
{
	int32 trackId = bIsTheme ? reactional_get_theme(FReactionalEngine::GetEngine()->reactionallib_ptr()) : reactional_get_track(FReactionalEngine::GetEngine()->reactionallib_ptr());
	if (trackId >= 0)
	{
		int32 nbrOfParams = reactional_get_num_params(FReactionalEngine::GetEngine()->reactionallib_ptr(), trackId);
		for (int32 i = 0; i < nbrOfParams; i++)
		{
			const char* stringchar = reactional_get_param_name(FReactionalEngine::GetEngine()->reactionallib_ptr(), trackId, i);
			FString strName(ANSI_TO_TCHAR(stringchar));
			if (!strName.IsEmpty() && !strName.StartsWith(TEXT("t_")))
			{
				ParameterNames.Add(strName);
			}
		}
	}
}

void UReactionalBPLibrary::GetParametersMap(bool bIsTheme, TMap<FString, FReactionalParameterValue> &ParametersMap)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()

	int32 trackId = bIsTheme
		? reactional_get_theme(lib_ptr)
		: reactional_get_track(lib_ptr);
	
	if (trackId >= 0)
	{
		int32 nbrOfParams = reactional_get_num_params(lib_ptr, trackId);
		for (int32 i = 0; i < nbrOfParams; i++)
		{
			FString MapKey;
			FReactionalParameterValue MapValue;
			bool bAddToMap = false;

			const char* stringchar = reactional_get_param_name(lib_ptr, trackId, i);
			FString strName(ANSI_TO_TCHAR(stringchar));

			if (!strName.IsEmpty() && !strName.StartsWith(TEXT("t_")))
			{
				MapKey = strName;

				int32 CheckParamType = reactional_get_param_type(lib_ptr, trackId, i);
				if (CheckParamType >= 0)
				{
					EReactionalParameterType ParamType = EReactionalParameterType((uint8(CheckParamType)));
					if (ParamType == EReactionalParameterType::ParameterType_String)
					{
						TArray<char> charBuf;
						charBuf.AddZeroed(512);
						charBuf[511] = '\0';

						int32 result = reactional_get_param_string(lib_ptr, trackId, i, charBuf.GetData(), 511);
						if (result > 0)
						{
							MapValue.ParamType = EReactionalParameterType::ParameterType_String;
							MapValue.strValue = ANSI_TO_TCHAR(charBuf.GetData());
							bAddToMap = true;
						}
					}
					else if (ParamType == EReactionalParameterType::ParameterType_Int)
					{
						int64_t value = std::numeric_limits<int64_t>::max();
						int32 result = reactional_get_param_int(lib_ptr, trackId, i, (int64_t*)&value);
						MapValue.ParamType = EReactionalParameterType::ParameterType_Int;
						MapValue.intValue = value;
						bAddToMap = true;
					}
					else if (ParamType == EReactionalParameterType::ParameterType_Float)
					{
						double value = std::numeric_limits<double>::max();
						int32 result = reactional_get_param_float(lib_ptr, trackId, i, &value);
						MapValue.ParamType = EReactionalParameterType::ParameterType_Float;
						MapValue.floatValue = (float)value;
						bAddToMap = true;
					}
					else if (ParamType == EReactionalParameterType::ParameterType_Bool)
					{
						bool value = false;
						int32 result = reactional_get_param_bool(lib_ptr, trackId, i, &value);
						if (result == 0)
						{
							MapValue.boolValue = value;
							bAddToMap = true;
						}
					}
				}
				if (bAddToMap)
				{
					ParametersMap.Add(MapKey, MapValue);
				}
			}
		}
	}
}

void UReactionalBPLibrary::DBGPrintParametersMap(const TMap<FString, FReactionalParameterValue> &ParametersMap)
{
	for (auto Iter = ParametersMap.CreateConstIterator(); Iter; ++Iter)
	{
		FString DbgParameterStr;
		if (Iter.Value().ParamType == EReactionalParameterType::ParameterType_Bool)
		{
			DbgParameterStr = FString::Printf(TEXT("%s: ParameterType_Bool, value: %d"), *Iter.Key(), int32(Iter.Value().boolValue));
		}
		if (Iter.Value().ParamType == EReactionalParameterType::ParameterType_Float)
		{
			DbgParameterStr = FString::Printf(TEXT("%s: ParameterType_Float, value: %f"), *Iter.Key(), Iter.Value().floatValue);
		}
		if (Iter.Value().ParamType == EReactionalParameterType::ParameterType_Int)
		{
			DbgParameterStr = FString::Printf(TEXT("%s: ParameterType_Int, value: %d"), *Iter.Key(), Iter.Value().intValue);
		}
		if (Iter.Value().ParamType == EReactionalParameterType::ParameterType_String)
		{
			DbgParameterStr = FString::Printf(TEXT("%s: ParameterType_String, value: %s"), *Iter.Key(), *Iter.Value().strValue);
		}
		REACTIONAL_LOG("DBGPrintParametersMap %s", *DbgParameterStr)
	}
}

FString UReactionalBPLibrary::GetParameterValueAsString(const FReactionalParameterValue &ParameterValue, bool &bWasSuccessful)
{
	if (ParameterValue.ParamType == EReactionalParameterType::ParameterType_String)
	{
		bWasSuccessful = true;
		return ParameterValue.strValue;
	}
	bWasSuccessful = false;
	return FString(TEXT("Error not string parameter value"));
}

int32 UReactionalBPLibrary::GetParameterValueAsInt(const FReactionalParameterValue &ParameterValue, bool &bWasSuccessful)
{
	if (ParameterValue.ParamType == EReactionalParameterType::ParameterType_Int)
	{
		bWasSuccessful = true;
		return ParameterValue.intValue;
	}
	bWasSuccessful = false;
	return std::numeric_limits<int32>::max();
}

float UReactionalBPLibrary::GetParameterValueAsFloat(const FReactionalParameterValue &ParameterValue, bool &bWasSuccessful)
{
	if (ParameterValue.ParamType == EReactionalParameterType::ParameterType_Float)
	{
		bWasSuccessful = true;
		return ParameterValue.floatValue;
	}
	bWasSuccessful = false;
	return std::numeric_limits<float>::max();
}

bool UReactionalBPLibrary::GetParameterValueAsBool(const FReactionalParameterValue &ParameterValue, bool &bWasSuccessful)
{
	if (ParameterValue.ParamType == EReactionalParameterType::ParameterType_Bool)
	{
		bWasSuccessful = true;
		return ParameterValue.boolValue;
	}
	bWasSuccessful = false;
	return false;
}

#pragma optimize("", on)

#undef LOCTEXT_NAMESPACE
