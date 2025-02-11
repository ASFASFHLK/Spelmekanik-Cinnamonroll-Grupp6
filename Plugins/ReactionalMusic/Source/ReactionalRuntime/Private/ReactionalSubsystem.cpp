/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalSubsystem.h"

#include "Engine.h"
#include "AudioDevice.h"
#include "ReactionalBPLibrary.h"
#include "ReactionalAsync.h"
#include "ReactionalSettings.h"
#include "ReactionalSynthComponent.h"

#define LOCTEXT_NAMESPACE "ReactionalMusic"
#pragma optimize("", off)

void UReactionalSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	REACTIONAL_LOG("Starting Reactional Subsystem")
	Super::Initialize(Collection);
	
	//____________________
	// Settings
	Settings = GetMutableDefault<UReactionalSettings>();
	if(!Settings)
	{
		REACTIONAL_LOG_WARNING("Could not load reactional settings.")
		return;
	}
	
	EngineProcessThreadingMode = Settings->EngineProcessThreadingMode;
	EngineRenderAudioMode	   = Settings->EngineRenderAudioMode;
	
	if(Settings->bShouldAutoloadBundles) { ReAutoloadBundles(Settings->AutoloadBundles); }

#if WITH_EDITOR
	int _LogLevel = static_cast<int>(Settings->InternalLogLevel);
	reactional_set_log_level(_LogLevel);
	reactional_set_log_callback(ReactionalLogCallback);
#endif
#if UE_BUILD_DEBUG
	reactional_set_log_level(static_cast<int>(EReactionalLogLevel::Debug));
	reactional_set_log_callback(ReactionalLogCallback);
#endif
	
	//____________________
	// Post init delegate
	FCoreDelegates::OnPostEngineInit.AddLambda([this] {
		REACTIONAL_LOG("Post engine init.")
		if(Settings->bAutoInitializeEngineInstance)
		{
			UReactionalSetupEngineLibrary::Setup_InitializeReactionalEngine();
		}
		else REACTIONAL_LOG("Skipping automatic engine initialization")
	});

	//____________________
	// Game instance start
	FWorldDelegates::OnStartGameInstance.AddLambda([this](const UGameInstance*){
		InitializeAudioForDevice();
	});
	
#if WITH_EDITOR
	FEditorDelegates::OnEditorInitialized.AddLambda([this](double) {
		InitializeAudioForDevice();
	});
	//____________________
	// End Play in Editor
	FEditorDelegates::EndPIE.AddLambda([this](const bool) {
		if(InternalAudioComponent != nullptr)
		{
			InternalAudioComponent->Stop();
			InternalAudioComponent->DestroyComponent();
		}
		UReactionalBPLibrary::PlaylistStop();
		UReactionalBPLibrary::ThemeStop();
		REACTIONAL_GET_LIB_PTR_OR_RETURN()

		reactional_unset_theme(lib_ptr);
		CurrentSelectedTheme = -1;
		reactional_unset_track(lib_ptr);
		CurrentSelectedTrack = -1;
		
		if(!Settings->bShouldAutoloadBundles)
		{
			ClearBundles();
		}
		else
		{
			LoadedBundles.Empty();
			TArray<FReactionalThemeInfo> tmp_themes;
			for(auto theme : LoadedThemes)
			{
				if(theme.bPersist) { tmp_themes.Add(theme); }
				else
				{
					auto result = reactional_remove_track(lib_ptr, theme.themeID);
					if(result < 0)
					{
						auto error = reactional_string_error(result);
						REACTIONAL_LOG_WARNING("Failed to remove track with id %d. Reason: %hs", theme.themeID, error)
					}
				}
			}
			LoadedThemes.Empty();
			LoadedThemes = tmp_themes;
			
			TArray<FReactionalTrackInfo> tmp_tracks;
			for(auto track : LoadedTracks)
			{
				if(track.bPersist) { tmp_tracks.Add(track); }
				else
				{
					auto result = reactional_remove_track(lib_ptr, track.trackID);
					if(result < 0)
					{
						auto error = reactional_string_error(result);
						REACTIONAL_LOG_WARNING("Failed to remove track with id %d. Reason: %hs", track.trackID, error)
					}
				}
			}
			LoadedTracks.Empty();
			LoadedTracks = tmp_tracks;
		}
		reactional_reset(lib_ptr);
		InitializeAudioForDevice(GEditor->GetMainAudioDeviceRaw());
	});
#endif
}

void UReactionalSubsystem::InitializeAudioForDevice(FAudioDevice* AudioDevice)
{
	if(InternalAudioComponent != nullptr)
	{
		if(InternalAudioComponent->IsPlaying()) { InternalAudioComponent->Stop(); }
		InternalAudioComponent->Deactivate();
		InternalAudioComponent->DestroyComponent();
	}
	if(SynthComponent != nullptr)
	{
		if(SynthComponent->IsPlaying())
		{
			SynthComponent->Stop();
		}
		SynthComponent->GetAudioComponent()->Deactivate();
		SynthComponent->Deactivate();
		SynthComponent->DestroyComponent();
	}
	
	if(EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioSynthComponent)
	{
		SynthComponent = NewObject<UReactionalSynthComponent>();
		SynthComponent->Activate();
		// gin:
		//	we deactivate the synth component's internal audio component as we want a component that won't be
		//	flushed or destroyed (created bellow). The internal component is also impossible/hard to edit since private.
		//	If we don't do this there will be two components receiving the same audio source resulting in crackling.
		//	todo: make a custom USynthComponent implementation, not just inherit
		SynthComponent->GetAudioComponent()->Deactivate();
		
		USynthSound* Synth = NewObject<USynthSound>();
		FAudioDevice::FCreateComponentParams Params = FAudioDevice::FCreateComponentParams(AudioDevice);
		InternalAudioComponent = FAudioDevice::CreateComponent(Synth, Params);
		if (InternalAudioComponent)
		{
			InternalAudioComponent->SetVolumeMultiplier(1);
			InternalAudioComponent->SetPitchMultiplier(1);
			InternalAudioComponent->bAllowSpatialization = false;
			InternalAudioComponent->bIsUISound = true;
			InternalAudioComponent->bAutoDestroy = false;
			InternalAudioComponent->bIgnoreForFlushing = true;
			InternalAudioComponent->bStopWhenOwnerDestroyed = false;
			InternalAudioComponent->Activate();
		}
		else REACTIONAL_LOG_ERROR("Failed to create audio component.")
		
		int32 sample_rate = AudioDevice->GetSampleRate();
		int32 buffer_length = AudioDevice->GetBufferLength();
		Synth->Init(SynthComponent, 2, sample_rate, buffer_length);
	}
	else if(EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds)
	{
		USoundBase* Sound = Settings->SoundAsset.LoadSynchronous();
		if(Sound == nullptr)
		{
			REACTIONAL_LOG_WARNING("No valid sound component set in settings. Defaulting to bundled asset.")
			Sound = TSoftObjectPtr<USoundBase>(FSoftObjectPath(TEXT("/ReactionalMusic/ReactionalSample.ReactionalSample"))).LoadSynchronous();
			if(Sound == nullptr)
			{
				REACTIONAL_LOG_ERROR("Failed getting default bundled sound asset. A MetaSound source is required for MetaSound render mode.")
				return;
			}
		}
		FAudioDevice::FCreateComponentParams Params = FAudioDevice::FCreateComponentParams(AudioDevice);
		InternalAudioComponent = FAudioDevice::CreateComponent(Sound, Params);
		if (InternalAudioComponent)
		{
			InternalAudioComponent->SetVolumeMultiplier(1);
			InternalAudioComponent->SetPitchMultiplier(1);
			InternalAudioComponent->bAllowSpatialization = false;
			InternalAudioComponent->bIsUISound = true;
			InternalAudioComponent->bAutoDestroy = false;
			InternalAudioComponent->bIgnoreForFlushing = true;
			InternalAudioComponent->bStopWhenOwnerDestroyed = false;
			InternalAudioComponent->Activate();
			InternalAudioComponent->Play();
		}
		else REACTIONAL_LOG_ERROR("Failed to create audio component.")
	}

	UReactionalSetupEngineLibrary::Engine_InitAudio();
}

void UReactionalSubsystem::ClearBundles()
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN()
	LoadedBundles.Empty();
	for(auto theme : LoadedThemes)
	{
		auto result = reactional_remove_track(lib_ptr, theme.themeID);
		if(result < 0)
		{
			auto error = reactional_string_error(result);
			REACTIONAL_LOG_WARNING("Failed to remove track with id %d. Reason: %hs", theme.themeID, error)
		}
	}
	LoadedThemes.Empty();
	for(auto track : LoadedTracks)
	{
		auto result = reactional_remove_track(lib_ptr, track.trackID);
		if(result < 0)
		{
			auto error = reactional_string_error(result);
			REACTIONAL_LOG_WARNING("Failed to remove track with id %d. Reason: %hs", track.trackID, error)
		}
	}
	LoadedTracks.Empty();
}

void UReactionalSubsystem::ReAutoloadBundles(TArray<TSoftObjectPtr<UReactionalBundleDataAsset>> Bundles)
{
	ClearBundles();
	for (TSoftObjectPtr<UReactionalBundleDataAsset> AutoloadBundle : Bundles)
	{
		if(AutoloadBundle.IsNull())
		{
			REACTIONAL_LOG("Invalid bundle in array.")
			continue;
		}
		
		auto Bundle = AutoloadBundle.LoadSynchronous();
		AsyncTask(ENamedThreads::Type::HighTaskPriority,[=]
		{
			REACTIONAL_LOG("Started autoloading bundle.")
			UReactionalSubsystem* Subsystem = GEngine->GetEngineSubsystem<UReactionalSubsystem>();
		
			//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation while we are running the async task
			Subsystem->ReactionalEnginePtr = FReactionalEngine::MakeSharedInstance().ToSharedRef();

			UReactionalBundleDataAsset* DataAssetObjectPtr = nullptr;
			if(!Reactional::LoadDataAssetPackageObj_Impl(Bundle, EReactionalAsyncBPThreadingMode::GameThread_Synchronous, DataAssetObjectPtr))
			{
				REACTIONAL_LOG_ERROR("Failed loading data asset.")
				return;
			}

			TArray<FReactionalParsedJsonDataElement> JsonData;
			TArray<FReactionalParsedJsonSectionsElement> JsonSections;

			if(!Reactional::ParseJSONManifest_Impl(
				FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
				JsonData,
				JsonSections
			)) {
				REACTIONAL_LOG_ERROR("Failed parsing JSON manifest.")
				return;
			}
		
			TArray<FReactionalThemeInfo> ThemesTrackInfo;
			TArray<FReactionalTrackInfo> PlayListTrackInfo;
			Reactional::AddBundleAssetsData_Impl(
				FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
				JsonData,
				JsonSections,
				ThemesTrackInfo,
				PlayListTrackInfo
			);
			for (auto Data : ThemesTrackInfo)
			{
				if(!Subsystem->LoadedThemes.ContainsByPredicate([&Data](const auto& Item) {
					return Item.themeHash == Data.themeHash;
				})) {
					//REACTIONAL_LOG("Adding theme: %s", *Data.trackName)
					Data.bPersist = true;
					Subsystem->LoadedThemes.Emplace(Data);
				}
			}
			for (auto Data : PlayListTrackInfo)
			{
				if(!Subsystem->LoadedTracks.ContainsByPredicate([&Data](const auto& Item) {
					return Item.trackHash == Data.trackHash;
				})) {
					//REACTIONAL_LOG("Adding track: %s", *Data.trackName)
					Data.bPersist = true;
					Subsystem->LoadedTracks.Emplace(Data);
				}
			}
		
			if(!Subsystem->LoadedBundles.ContainsByPredicate([&DataAssetObjectPtr](const auto& Item) {
				return Item->Bundle.BundlePath == DataAssetObjectPtr->Bundle.BundlePath;
			})) {
				//REACTIONAL_LOG("Adding bundle: %s", *DataAssetObjectPtr->Bundle.BundleManifestString)
				Subsystem->LoadedBundles.Emplace(DataAssetObjectPtr);
			}
			REACTIONAL_LOG("Finished autoloading bundle.")
		});
	}
}

#pragma optimize("", on)
#undef LOCTEXT_NAMESPACE