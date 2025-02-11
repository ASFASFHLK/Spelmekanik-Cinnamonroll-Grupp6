/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "ReactionalEngine.h"
#include "ReactionalSubsystem.h"

#include "ReactionalSettings.generated.h"

//____________________________________________
// FReactionalSettings
/**
 * Reactional plugin default settings
 */
UCLASS(config = Game, DefaultConfig, meta = (DisplayName="Reactional Music"))
class REACTIONALRUNTIME_API UReactionalSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/**
	 * Will initialize the Reactional Engine instance when subsystem is initialized
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ReactionalMusic)
	bool bAutoInitializeEngineInstance = true;

	/**
	 * Automatically loads the bundles specified in BundleCollectionPath
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ReactionalMusic)
	bool bShouldAutoloadBundles = true;
	
	/**
	 * Automatically loads the bundles specified when 'Should Autoload Bundles' is set to true.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ReactionalMusic)
	TArray<TSoftObjectPtr<UReactionalBundleDataAsset>> AutoloadBundles = {
	    TSoftObjectPtr<UReactionalBundleDataAsset>(FSoftObjectPath(TEXT("/ReactionalMusic/ReactionalPluginBundle/ReactionalPluginBundle.ReactionalPluginBundle"))),
	};

	/**
	 * Log level for the internal reactional engine, levels are listed in increasing order.
	 * Levels below the selected will also be active.
	 */
	UPROPERTY(Config, EditAnywhere, meta=(ConsoleVariable="Reactional.LogLevel"), Category = ReactionalMusic)
	EReactionalLogLevel InternalLogLevel = EReactionalLogLevel::Error;

	/**
	 * Designates mode to render audio through.
	 * @note MetaSound mode requires valid sound asset to be set.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(DisplayName = "Render Mode"), Category = ReactionalMusic)
	EReactionalRenderMode EngineRenderAudioMode = EReactionalRenderMode::ReactionalRenderAudioSynthComponent;

	/**
	 * Designates if the engine process will occur on the main thread or on a dedicated one.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true", DisplayName = "Threading Mode"), Category = ReactionalMusic)
	EReactionalThreadingMode EngineProcessThreadingMode = EReactionalThreadingMode::DedicatedThread;

	/**
	 * Lookahead time in microseconds for event scheduling on the audio thread. 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ReactionalMusic)
	int32 LookaheadMilliseconds = 32;

	/**
	 * Asset to use for MetaSound render mode.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = ReactionalMusic)
	TSoftObjectPtr<USoundBase> SoundAsset;

	//_____________________
	// Runtime updates

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override
	{
	    Super::PostEditChangeProperty(Event);
		
	    UReactionalSubsystem* subsystem = GEngine->GetEngineSubsystem<UReactionalSubsystem>();
		if(!subsystem || !Event.Property) { return; }
	
		if (Event.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UReactionalSettings, bShouldAutoloadBundles))
		{
			if(!bShouldAutoloadBundles)
			{
				REACTIONAL_GET_LIB_PTR_OR_RETURN()
				subsystem->ClearBundles();
				reactional_reset(lib_ptr);
			}
			else
			{
				subsystem->ReAutoloadBundles(AutoloadBundles);
			}
		}
		
		if (Event.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UReactionalSettings, AutoloadBundles))
		{
			if(Event.ChangeType == EPropertyChangeType::ArrayClear)
			{
				REACTIONAL_GET_LIB_PTR_OR_RETURN()
				subsystem->ClearBundles();
				reactional_reset(lib_ptr);
			}
			else if(bShouldAutoloadBundles)
			{
				REACTIONAL_LOG("AutoloadBundles was modified. Reloading bundles...");
				subsystem->ReAutoloadBundles(AutoloadBundles);
			}
		}
		
		if (Event.Property->GetFName() ==  GET_MEMBER_NAME_CHECKED(UReactionalSettings, InternalLogLevel))
		{
			int log_level = static_cast<int>(InternalLogLevel);
			reactional_set_log_level(log_level);
		}
		
		if (Event.Property->GetFName() ==  GET_MEMBER_NAME_CHECKED(UReactionalSettings, EngineProcessThreadingMode))
		{
			subsystem->EngineProcessThreadingMode = EngineProcessThreadingMode;
		}
		
		if (Event.Property->GetFName() ==  GET_MEMBER_NAME_CHECKED(UReactionalSettings, EngineRenderAudioMode))
		{
			subsystem->EngineRenderAudioMode = EngineRenderAudioMode;
		}
		
		if (Event.Property->GetFName() ==  GET_MEMBER_NAME_CHECKED(UReactionalSettings, LookaheadMilliseconds))
		{
			REACTIONAL_GET_LIB_PTR_OR_RETURN()
			int32 paramIdx = reactional_find_param(lib_ptr, -1, TCHAR_TO_ANSI(TEXT("lookahead")));
			subsystem->lookaheadMilliseconds = LookaheadMilliseconds;
			int32 lookaheadValue = LookaheadMilliseconds * 1000;
			REACTIONAL_LOG("Lookahead set to: %d", lookaheadValue)
			reactional_set_param_int(lib_ptr, -1, paramIdx, lookaheadValue);
		}
		
		if (Event.Property->GetFName() ==  GET_MEMBER_NAME_CHECKED(UReactionalSettings, SoundAsset))
		{
			if(SoundAsset.IsNull()) { return; }
			
			if(GEditor->IsSimulatingInEditor())
			{
				subsystem->InitializeAudioForDevice(GEditor->GetMainAudioDeviceRaw());
			}
			else
			{
				subsystem->InitializeAudioForDevice();
			}
		}
	}
#endif
};
