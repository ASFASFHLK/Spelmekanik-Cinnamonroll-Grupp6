/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "ReactionalEngine.h"
#include "UnrealEngine.h" // may be grayed out, but needed for non Unity build
#include "Subsystems/EngineSubsystem.h"
#include "ReactionalSubsystem.generated.h"

//____________________________________________
// UReactionalSubsystem

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FReactionalSubsystemNoteOnEventMCDelegate, double, offset, int32, sink, int32, lane, float, pitch, float, velocity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FReactionalSubsystemNoteOffEventMCDelegate, double, offset, int32, sink, int32, lane, float, pitch, float, velocity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReactionalSubsystemStingerEventMCDelegate, double, offset, bool, startevent, int32, stingerOrigin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReactionalSubsystemAudioEventMCDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReactionalSubsystemBarBeatEventMCDelegate, double, offset, int32, bar, int32, beat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReactionalSubsystemPartEventMCDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReactionalSubsystemSuccessFailedTaskPin, const FString&, ErrorString);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReactionalQuantizationEventMCDelegate);

UCLASS(DisplayName="Reactional Subsystem")
class REACTIONALRUNTIME_API UReactionalSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
	void Initialize(FSubsystemCollectionBase& Collection) override;

	bool ShouldCreateSubsystem(UObject* Outer) const override { return !IsRunningDedicatedServer(); }

	UPROPERTY(EditAnywhere, Category = ReactionalMusic)
	class UReactionalSettings* Settings; friend UReactionalSettings;

	void ReAutoloadBundles(TArray<TSoftObjectPtr<UReactionalBundleDataAsset>> Bundles);

	void ClearBundles();

	UPROPERTY()
	class UAudioComponent* InternalAudioComponent;
	UPROPERTY()
	class UReactionalSynthComponent* SynthComponent;
	
	void InitializeAudioForDevice(FAudioDevice* AudioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice());
	
public:
	static UReactionalSubsystem* GetSubsystem() { return GEngine->GetEngineSubsystem<UReactionalSubsystem>(); }

	UReactionalSettings* GetSettings() const { return Settings; }

	TSharedPtr<FReactionalEngine> ReactionalEnginePtr;

	//_______________________
	// Runtime info
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, DisplayName="Loaded Themes"), Category = ReactionalMusic)
	TArray<FReactionalThemeInfo> LoadedThemes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, DisplayName="Loaded Tracks"), Category = ReactionalMusic)
	TArray<FReactionalTrackInfo> LoadedTracks;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = true, DisplayName="Loaded Bundle"), Category = ReactionalMusic)
	TArray<UReactionalBundleDataAsset*> LoadedBundles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ReactionalMusic)
	int32 lookaheadMilliseconds = 32;

	mutable int32 CurrentSelectedTheme = -1;
	mutable int32 CurrentSelectedTrack = -1;
	
	mutable bool bIsDucked;
	mutable float CurrentlySetTrackVolume = 1.f;
	
	//_______________________
	// Mode settings
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Render Mode"), Category = ReactionalMusic)
	EReactionalRenderMode EngineRenderAudioMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true, DisplayName = "Threading Mode"), Category = ReactionalMusic)
	EReactionalThreadingMode EngineProcessThreadingMode;

	//_______________________
	// Delegates

	UPROPERTY(BlueprintAssignable, DisplayName = OnNoteOnEvent, Category = "ReactionalMusic|Events")
	FReactionalSubsystemNoteOnEventMCDelegate NoteOnEvent;

	UPROPERTY(BlueprintAssignable, DisplayName = OnNoteOffEvent, Category = "ReactionalMusic|Events")
	FReactionalSubsystemNoteOffEventMCDelegate NoteOffEvent;

	UPROPERTY(BlueprintAssignable, DisplayName = OnAudioEndEvent, Category = "ReactionalMusic|Events")
	FReactionalSubsystemAudioEventMCDelegate AudioEndEvent;

	UPROPERTY(BlueprintAssignable, DisplayName = OnBarBeatEvent, Category = "ReactionalMusic|Events")
	FReactionalSubsystemBarBeatEventMCDelegate BarBeatEvent;
	
	UPROPERTY(BlueprintAssignable, DisplayName = OnPartEvent, Category = "ReactionalMusic|Events")
	FReactionalSubsystemPartEventMCDelegate PartEvent;
	
	struct FReactionalDelegateData { FReactionalQuantizationEventMCDelegate Delegate; int64 LastQuant; };
	FReactionalDelegateData QuantizationEvents[static_cast<int>(EReactionalQuantizationValue::Count)];
};
