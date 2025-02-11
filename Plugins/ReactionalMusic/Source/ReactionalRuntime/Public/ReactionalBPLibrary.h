/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReactionalEngine.h"
#include "ReactionalAsync.h"
#include "ReactionalSubsystem.h"
#include "ReactionalBPLibrary.generated.h"

//Proxy BP object
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuccessFailedTaskPin, const FString&, ErrorString);

UENUM()
enum EReactionalAsset : uint8
{
	Track,
	Theme,
};

inline const char* to_string(EReactionalAsset e)
{
	switch (e)
	{
	case Track: return "Track";
	case Theme: return "Theme";
	default: return "unknown";
	}
}

UCLASS(meta=(ReactionalAsyncExecNode))
class REACTIONALRUNTIME_API UReactionalAsyncTaskBPProxy : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	/** Default UObject constructor */
	UReactionalAsyncTaskBPProxy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	virtual void Activate();

	virtual void RegisterWithGameInstance(UObject* WorldContextObject);
	virtual void SetReadyToDestroy();

	UPROPERTY(BlueprintAssignable)
	FSuccessFailedTaskPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSuccessFailedTaskPin OnFailed;

	/**
	 * Loads all content in given asset bundle.
	 * @param WorldContextObject UObject registered to a UWorld.
	 * @param AssetBundle Reactional data asset to load bundle from.
	 * @param ThreadingMode Decides if loading should be done on game thread or on separate worker thread. Game thread is blocking.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta=(DisplayName = "LoadBundle", BlueprintInternalUseOnly = "true", WorldContext=WorldContextObject))
	static UReactionalAsyncTaskBPProxy* Setup_LoadDataAssetBundle(
		UObject* WorldContextObject,
		TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
		EReactionalAsyncBPThreadingMode ThreadingMode = EReactionalAsyncBPThreadingMode::PooledThread_Async
	);
	
	/**
	 * Loads section with corresponding name from given asset bundle.
	 * @note If name is left blank then the first section will be loaded.
	 * @param WorldContextObject UObject registered to a UWorld.
	 * @param AssetBundle Reactional data asset to load bundle from.
	 * @param SectionName Name of the track to load.
	 * @param ThreadingMode Decides if loading should be done on game thread or on separate worker thread. Game thread is blocking.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta=(DisplayName = "LoadSection", BlueprintInternalUseOnly = "true", WorldContext=WorldContextObject))
	static UReactionalAsyncTaskBPProxy* Setup_LoadDataAssetSection(
		UObject* WorldContextObject,
		TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
		FString SectionName = "",
		EReactionalAsyncBPThreadingMode ThreadingMode = EReactionalAsyncBPThreadingMode::PooledThread_Async
	);
	
	/**
	 * Loads playlist with corresponding name from given asset bundle.
	 * @note If name is left blank then the playlist from the first section will be loaded.
	 * @param WorldContextObject UObject registered to a UWorld.
	 * @param AssetBundle Reactional data asset to load bundle from.
	 * @param PlaylistName Name of the track to load.
	 * @param ThreadingMode Decides if loading should be done on game thread or on separate worker thread. Game thread is blocking.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta=(DisplayName = "LoadPlaylist", BlueprintInternalUseOnly = "true", WorldContext=WorldContextObject))
	static UReactionalAsyncTaskBPProxy* Setup_LoadDataAssetPlaylist(
		UObject* WorldContextObject,
		TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
		FString PlaylistName = "",
		EReactionalAsyncBPThreadingMode ThreadingMode = EReactionalAsyncBPThreadingMode::PooledThread_Async
	);

	/**
	 * Loads track with corresponding name from given asset bundle.
	 * @note If name is left blank then the first track of the first section will be loaded.
	 * @param WorldContextObject UObject registered to a UWorld.
	 * @param AssetBundle Reactional data asset to load bundle from.
	 * @param TrackName Name of the track to load.
	 * @param ThreadingMode Decides if loading should be done on game thread or on separate worker thread. Game thread is blocking.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta=(DisplayName = "LoadTrack", BlueprintInternalUseOnly = "true", WorldContext=WorldContextObject))
	static UReactionalAsyncTaskBPProxy* Setup_LoadDataAssetTrack(
		UObject* WorldContextObject,
		TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
		FString TrackName = "",
		EReactionalAsyncBPThreadingMode ThreadingMode = EReactionalAsyncBPThreadingMode::PooledThread_Async
	);

	/**
	 * Loads theme with corresponding name from given asset bundle.
	 * @note If name is left blank then the first theme of the first section will be loaded.
	 * @param WorldContextObject UObject registered to a UWorld.
	 * @param AssetBundle Reactional data asset to load bundle from.
	 * @param ThemeName Name of the theme to load.
	 * @param ThreadingMode Decides if loading should be done on game thread or on separate worker thread. Game thread is blocking.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta=(DisplayName = "LoadTheme", BlueprintInternalUseOnly = "true", WorldContext=WorldContextObject))
	static UReactionalAsyncTaskBPProxy* Setup_LoadDataAssetTheme(
		UObject* WorldContextObject,
		TSoftObjectPtr<UReactionalBundleDataAsset> AssetBundle,
		FString ThemeName = "",
		EReactionalAsyncBPThreadingMode ThreadingMode = EReactionalAsyncBPThreadingMode::PooledThread_Async
	);

	// markus:
	//	Since we share one proxy object for all the latent/async BP nodes,
	//	not all the stored input parameters are used in a given node, hence the TOptional
	
	TOptional<FString> FilePath;
	TOptional<TSoftObjectPtr<UReactionalBundleDataAsset>> BundleSoftObjectPtr;

	TWeakObjectPtr<UReactionalSubsystem> Subsystem;
	
	EReactionalAsyncBPThreadingMode AsyncBPTaskThreadingMode;
	EReactionalAsyncBPTaskType AsyncBPTaskType;

	TSharedPtr<FReactionalAsyncBPTask> AsyncBPTask;

protected:
	virtual void RegisterWithGameInstance(UGameInstance* GameInstance);

	TWeakObjectPtr<UGameInstance> RegisteredWithGameInstance;

	//~ Begin FTickableObject Interface
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override   { return !HasAnyFlags(RF_ClassDefaultObject) && bShouldTick; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UReactionalAsyncTaskBlueprintProxy, STATGROUP_Tickables); }
	//~ End FTickableObject Interface

	virtual void ReportSuccess();
	virtual void ReportFailure();

	/** True until the async task completes, then false */
	bool bShouldTick;
};

UCLASS()
class REACTIONALRUNTIME_API UReactionalSetupEngineLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	// Checks the validity of the ReactionalManager instance.
	// Returns true if a valid instance exists; otherwise logs an error and returns false.
	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta=(DisplayName = "Is Valid", WorldContext = "WorldContextObject"))
	//static bool Instance_IsValid();

	/**
	 * Creates and Initialize the ReactionalMusic Engine Instance
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta = (DisplayName = "Initialize engine"))
	static bool Setup_InitializeReactionalEngine();
	
	// markus?:
	//	Seems heavy and should potentially be ASync? In practice though we should not free and recreate this frequently
	/**
	 * Free the engine instance
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta = (DisplayName = "Free Reactional Engine"))
	static void Setup_FreeEngineInstance();
	
	/**
	 * Remove a track or theme from the engine, freeing its resources.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Setup", meta = (DisplayName = "Remove Asset"))
	static void Setup_RemoveAsset(EReactionalAsset asset_type, const int id);

	/**
	 * Gets the sample rate of the engine
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Setup", meta = (DisplayName = "Get Engine Param SampleRate"))
	static double Engine_GetSampleRate();

	/**
	 * Sets the sample rate of the engine
	 * @param SampleRate The sample rate to set.
	 */
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Engine Param SampleRate", WorldContext = "WorldContextObject"), Category = "ReactionalMusic")
	static void Engine_SetSampleRate(double SampleRate);

	/**
	 * Gets the buffer size of the engine.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Engine Param BufferSize"), Category = "ReactionalMusic|Setup")
	static int32 Engine_GetBufferSize();

	/**
	 * Sets the buffer size of the engine.
	 * @param BufferSize The buffer size to set.
	 */
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Engine Param BufferSize", WorldContext = "WorldContextObject"), Category = "ReactionalMusic")
	static void Engine_SetBufferSize(double BufferSize);

	static void Engine_SetAllowPlay(bool bAllowPlay);
	static bool Engine_GetAllowPlay();
	
	/**
	 * Initialize audio settings with specified buffer size and sample rate.
	 * @param BufferSize The buffer size to set, defaults to -1 for auto-detection.
	 * @param SampleRate The sample rate to set, defaults to -1 for auto detection.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init Audio", AdvancedDisplay=0), Category = "ReactionalMusic|Setup")
	static void Engine_InitAudio(int32 SampleRate = -1, int32 BufferSize = -1);
	
	static void ResetEngine_Impl(bool bFreeEngineInstance = true);
	
	static int32 GetAudioDeviceBufferSizeAsInt();
	static int32 GetAudioDeviceSampleRateAsInt();
};

UCLASS()
class REACTIONALRUNTIME_API UReactionalPlaybackLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Gets the loaded theme ID from the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static int32 Theme_GetID();

	/**
	 * Gets the info of the current theme in the playlist.
	 * @param OutThemeInfo FReactionalTrackInfo struct that will be get written to.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static bool Theme_GetCurrentThemeInfo(FReactionalThemeInfo& OutThemeInfo);

	/**
	 * Checks if a theme is loaded in the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static bool Theme_IsLoaded();

	/**
	 * Plays the currently loaded theme in the engine.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_Play();
	
	/**
	 * Sets theme with corresponding id as the active one in the engine.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_SetTheme(int id);
	
	/**
	 * Unsets theme in the engine.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_UnsetTheme();
	
	/**
	 * Gets the id of the active theme in the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static int Theme_GetTheme();

	/**
	 * Resets the current loaded theme in the engine.
	 * @note This will set the theme status to stopped.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_Reset();

	/**
	 * Stops the currently playing theme, if any, in the engine.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_Stop();

	/**
	 * Fades the current theme to the desired target amplitude/volume.
	 * @param Target The target amplitude/volume.
	 * @param FadeTime Time to fade over.
	 * @param Offset Delay before offset starts.
	 * @param bStopFinish If the theme should stop playing once fade has completed.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Theme Fade"), Category = "ReactionalMusic|Playback|Theme")
	static void Theme_Fade(const float Target, const float FadeTime = 0.f, const float Offset = 0.f, const bool bStopFinish = false);

	/**
	 * Gets the state of the current theme in the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static int32 Theme_State();

	/**
	 * Overrides the instrument settings for the theme.
	 * @param InstrumentName Name of the instrument.
	 * @param PulseRate Pulse rate for the instrument.
	 * @param Pitch Pitch of the instrument.
	 * @param Velocity Velocity of the instrument.
	 * @param Active Whether the instrument is active.
	 * @param Legato Legato value for the instrument.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_InstrumentOverride(
		FString InstrumentName,
		float PulseRate,
		float Pitch,
		float Velocity,
		bool Active,
		float Legato = 1.0f
	);

	/**
	 * Gets the list of overridable instruments for the current theme.
	 * @param Out Output array of all overridable instrument names.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_GetOverridableInstruments(TArray<FString>& Out);

	/**
	 * Triggers a stinger in the current theme with quantization.
	 * @param StingerName Name of the stinger.
	 * @param Quant The quantization value as an enum.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_TriggerStinger_Quant(FString StingerName, EReactionalQuantizationValue Quant);

	/**
	 * Triggers a stinger in the current theme with quantization.
	 * @param StingerName Name of the stinger.
	 * @param Value The quantization value as a float.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_TriggerStinger_Float(FString StingerName, float Value);

	/**
	 * Triggers a state change in the current theme
	 * @param StateName The name of the state.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_TriggerState(FString StateName);

	/**
	 * Gets the control settings for the current theme
	 * @param Out Output map of all controls. Control names as keys and FReactionalControlInfo structs as values.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_GetControls(TMap<FString, FReactionalControlInfo>& Out);
	
	/**
	 * Gets a control value for the current theme
	 * @param InControlName Name of the control.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static double Theme_GetControl(const FString& InControlName);

	/**
	 * Gets the current beat of the theme in the engine
	 */
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static float Theme_GetCurrentBeat();

	/**
	 * Gets the tempo of the theme in beats per minute
	 */
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static float Theme_GetBPM();

	/**
	 * Sets a control value for the current theme
	 * @param ControlName Name of the control.
	 * @param Value Value to set.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_SetControl(FString ControlName, float Value = 1.0f);

	/**
	 * Sets the volume for the current theme.
	 * @param Value Value to set. Clamped to 0-1.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Theme")
	static void Theme_SetVolume(float Value);

	/**
	 * Gets the volume of the current theme.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Theme")
	static float Theme_GetVolume();

	/**
	 * Gets the current beat of the current track in the playlist.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static float Playlist_GetCurrentBeat();

	/**
	 * Gets the tempo of the current track in beats per minute.
	 */
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static float Playlist_GetBPM();

	/**
	 * Gets the ID of the current track in the playlist.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static int32 Playlist_GetTrackID();

	/**
	 * Gets the metadata of the current track in the playlist.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static FString Playlist_GetCurrentTrackMetadata();

	/**
	 * Gets the info of the current track in the playlist.
	 * @param OutTrackInfo FReactionalTrackInfo struct that will be get written to.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist", meta=(WorldContext=WorldContextObject))
	static bool Playlist_GetCurrentTrackInfo(FReactionalTrackInfo& OutTrackInfo);

	/**
	 * Gets the index of the selected track in the playlist.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist", meta=(WorldContext=WorldContextObject))
	static int32 Playlist_GetSelectedTrackIndex();

	/**
	 * Fades the playlist to the desired target amplitude/volume.
	 * @param Target The target amplitude/volume.
	 * @param FadeTime Time to fade over.
	 * @param Offset Delay before offset starts.
	 * @param bStopFinish If the track should stop playing once fade has completed.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Playlist Fade"), Category = "ReactionalMusic|Playback|Playlist")	
	static void Playlist_Fade(const float Target, const float FadeTime = 0.f, const float Offset = 0.f, const bool bStopFinish = false);

	/**
	 * Plays a track in the playlist by name.
	 * @param TrackName Name of the track to play.
	 * @param FadeOutTime Fade-out time in seconds.
	 * @param FadeInTime Fade-in time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist", meta=(WorldContext=WorldContextObject))
	static void Playlist_PlayTrackByName(FString TrackName, float FadeOutTime = 0.1f, float FadeInTime = 0.f);

	/**
	 * Plays a track in the playlist by track info struct.
	 * @param TrackInfo Track info struct with data of the track to play.
	 * @param FadeOutTime Fade-out time in seconds.
	 * @param FadeInTime Fade-in time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist", meta=(WorldContext=WorldContextObject))
	static void Playlist_PlayTrackByTrackInfo(const FReactionalTrackInfo& TrackInfo, float FadeOutTime = 0.1f, float FadeInTime = 0.f);

	/**
	 * Plays a track in the playlist by index.
	 * @param TrackIndex Index of track to play.
	 * @param FadeOutTime Fade-out time in seconds.
	 * @param FadeInTime Fade-in time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist", meta=(WorldContext=WorldContextObject))
	static void Playlist_PlayTrackByIndex(int32 TrackIndex, float FadeOutTime = 0.1f, float FadeInTime = 0.0f);
	
		// markus?:
		//	Removed Blueprint callable 
	/**
	 * Copies the preroll settings from the specified track to the current theme.
	 * @param TrackId Index of the track to copy.
	 */
	UFUNCTION()
	static void Playlist_CopyPrerollToTheme(int32 TrackId);

	/**
	 * Checks if the playlist is loaded in the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static bool Playlist_IsLoaded();

	/**
	 * Moves to the next track in the playlist
	 * @param FadeOutTime Fade-out time in seconds.
	 * @param FadeInTime Fade-in time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist", meta=(WorldContext=WorldContextObject))
	static void Playlist_Next(float FadeOutTime = 0.1f, float FadeInTime = 0.0f);

	/**
	 * Moves to the previous track in the playlist
	 * @param FadeOutTime Fade-out time in seconds.
	 * @param FadeInTime Fade-in time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|playlist", meta=(WorldContext=WorldContextObject))
	static void Playlist_Prev(float FadeOutTime = 0.1f, float FadeInTime = 0.0f);

	/**
	 * Plays a random track from the playlist
	 * @param FadeOutTime Fade-out time in seconds.
	 * @param FadeInTime Fade-in time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist")
	static void Playlist_Random(float FadeOutTime = 0.1f, float FadeInTime = 0.0f);

	/**
	 * Stops the current track in the playlist
	 * @param FadeOutTime Fade-out time in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist")
	static void Playlist_Stop(float FadeOutTime = 0.1f);

	/**
	 * Plays the current track in the playlist.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist")
	static void Playlist_Play(float FadeInTime = 0.1f);
	
	/**
	 * Sets track with corresponding id as the active one in the engine.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist")
	static void Playlist_SetTrack(int id);
	
	/**
	 * Unsets track in the engine.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist")
	static void Playlist_UnsetTrack();
	
	/**
	 * Gets the id of the currently active track in the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static int Playlist_GetTrack();
	
	/**
	 * Gets the id of the currently active track in the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static int Playlist_GetNumTracks();

	/**
	 * Gets the state of the playlist in the engine.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static int32 Playlist_State();

	/**
	 * Sets the volume for the current playlist.
	 * @param Value Value to set. Clamped to 0-1.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|Playlist")
	static void Playlist_SetVolume(float Value);

	/**
	 * Gets the volume of the playlist.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|Playlist")
	static float Playlist_GetVolume();

	/**
	 * Schedules audio playback in the engine
	 * @param Sound Sound asset to schedule.
	 * @param Quant The quantization value.
	 * @param TimeOffset The time offset in seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|MusicSystem")
	static void MusicSystem_ScheduleAudio(USoundBase* Sound, float Quant, float TimeOffset);
	
	/**
	 * Gets the time to the next beat in the engine
	 * @param Quant The quantization value.
	 * @param Offset The offset in seconds.
	 * @param bTheme Whether to get the control from the theme or track.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static float MusicSystem_GetTimeToBeat(float Quant, float Offset = 0.0f, bool bTheme = true);

	/**
	 * Gets the real-time to the next beat in the engine
	 * @param Quant The quantization value.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static float MusicSystem_GetRealTimeToBeat(float Quant);
	
	/**
	 * Gets the next beat in the engine
	 * @param Quant The quantization value.
	 * @param Offset The offset in seconds.
	 * @param bTheme Whether to get the control from the theme or track.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static float MusicSystem_GetNextBeat(float Quant, float Offset = 0.0f, bool bTheme = true);
	
	/**
	 * Gets the absolute time to the next beat in the engine
	 * @param Quant The quantization value.
	 * @param Offset The offset in seconds.
	 * @param bTheme Whether to get the control from the theme or track.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static int64 MusicSystem_GetNextBeatAbsolute(double Quant, float Offset = 0.0f, bool bTheme = true);

	/**
	 * Gets the current beat position
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static float MusicSystem_GetCurrentBeat();

	/**
	 * Gets the current micro beat in the engine
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static double MusicSystem_GetCurrentMicroBeat();

	/**
	 * Gets the tempo in beats per minute of currently playing theme or track
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static float MusicSystem_GetBPM();

	/**
	 * Converts beats to seconds in the engine
	 * @param Beats The number of beats to convert.
	 */
	UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback|MusicSystem")
	static float MusicSystem_BeatsToSeconds(float Beats);

	/**
	 * Ducks the music to the desired Amp value.
	 * @note To return to un-ducked state call with an Amp value of 1.0f.
	 * @param Amp The number of beats to convert.
	 */
	UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback|MusicSystem")
	static void MusicSystem_DuckMusic(float Amp);
	
	/**
	 * Delay until next desired beat.
	 * @note To return to un-ducked state call with an Amp value of 1.0f.
	 * @param WorldContextObject UObject registered to a UWorld.
	 * @param LatentInfo Info struct for the LatentActionManager.
	 * @param Beat The beat duration to wait for.
	 * @param Offset The offset in beats.
	 */
	UFUNCTION(BlueprintCallable, Category="ReactionalMusic|Playback|MusicSystem", meta=(Latent, LatentInfo=LatentInfo, HidePin=WorldContextObject, DefaultToSelf=WorldContextObject))
	static void MusicSystem_WaitForNextBeat(UObject* WorldContextObject, FLatentActionInfo LatentInfo, float Beat, float Offset);

	/**
	 * Binds an event to a quantized value which will trigger during playback.
	 * @param Quant The quantized value of the event.
	 * @param OnQuantizationEvent Out event.
	 */
	UFUNCTION(BlueprintCallable, Category="ReactionalMusic|Playback|MusicSystem")
	static void MusicSystem_SubscribeToQuantizationEvent(EReactionalQuantizationValue Quant, const FReactionalQuantizationEvent& OnQuantizationEvent);

	static void Playlist_PlayTrackByID_Impl(int32 TrackID, float FadeOutTime, float FadeInTime);

	static void SetControl_Impl(const FString& ControlName, float Value = 1.f, bool bIsTheme = true);

private:
	static void ContinuePlayback(int32 TrackID, float FadeInTime);
	
	class REACTIONALRUNTIME_API FWaitForBeatLatentAction : public FPendingLatentAction
	{
	public:
		FWaitForBeatLatentAction(float Quant, float Beat, float Offset, const FLatentActionInfo& LatentInfo)
			: QuantBeat(Quant)
			, Beat(Beat)
			, Offset(Offset)
			, ExecutionFunction(LatentInfo.ExecutionFunction)
			, OutputLink(LatentInfo.Linkage)
			, CallbackTarget(LatentInfo.CallbackTarget)
		{}
		
		virtual void UpdateOperation(FLatentResponse& Response) override
		{
			int64 Microbeat = MusicSystem_GetCurrentMicroBeat();
			if ((QuantBeat - Microbeat) > (Beat + 1)) QuantBeat = MusicSystem_GetNextBeatAbsolute(Beat) + (Offset * 1000000.f);
			Done = (Microbeat >= QuantBeat);

			Response.FinishAndTriggerIf(Done, ExecutionFunction, OutputLink, CallbackTarget);
		}
		
	private:
		int64 QuantBeat;
		float Beat;
		float Offset;
		FName ExecutionFunction;
		int32 OutputLink;
		FWeakObjectPtr CallbackTarget;
		bool Done = false;
	};
};

UCLASS()
class REACTIONALRUNTIME_API UReactionalBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION( BlueprintCallable, Category = "ReactionalMusic|Playback")
	static void PlaylistStart(bool bRandomTrack);

	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback")
	static void PlaylistStop();

	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback")
	static void PlaylistNext();

	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback")
	static void ThemeStart();

	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback")
	static void ThemeStop();

	//// Gets the control names for the loaded theme
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Deprecated", meta=(Deprecated))
	static void GetControlNames(bool bIsTheme, TArray<FString>& ControlNames);

	//// Gets the parameter names for the loaded theme
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Deprecated", meta=(Deprecated))
	static void GetParameterNames(bool bIsTheme, TArray<FString>& ParameterNames);

	// Sets a float parameter value for loaded theme
	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback")
	static float SetFloatParameter(FString ParamName, float ParamValue, bool& bValid);

	// Sets an integer parameter value for the given actor
	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback")
	static int32 SetIntParameter(FString ParamName, int ParamValue, bool& bValid);

	// Gets the value of the specified control
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback")
	static float GetControlValue(FString ControlName);

	// Sets the value of the specified control
	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Playback")
	static void SetControlValue(FString ControlName, float ControlValue);

	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback")
	static float GetCurrentBeatAsFloat();

	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback")
	static int32 GetCurrentBeatAsInt();

	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback")
	static double GetCurrentBeatAsDouble();

	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback")
	static int64 GetNextQuantBeat(int64 in_quant, int64 in_phase);

	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Playback")
	static float GetBPM();

	//// Gets the parameters map for the given actor
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Dev")
	static void GetParametersMap(bool bIsTheme, TMap<FString, FReactionalParameterValue>& ParametersMap);

	//// Prints the parameters map for debugging purposes
	//UFUNCTION(BlueprintCallable, Category = "ReactionalMusic|Dev")
	static void DBGPrintParametersMap(const TMap<FString, FReactionalParameterValue>& ParametersMap);

	//// Gets the parameter value as a string
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Dev")
	static FString GetParameterValueAsString(const FReactionalParameterValue& ParameterValue, bool& bWasSuccessful);

	//// Gets the parameter value as an integer
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Dev")
	static int32 GetParameterValueAsInt(const FReactionalParameterValue& ParameterValue, bool& bWasSuccessful);

	//// Gets the parameter value as a float
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Dev")
	static float GetParameterValueAsFloat(const FReactionalParameterValue& ParameterValue, bool& bWasSuccessful);

	//// Gets the parameter value as a boolean
	//UFUNCTION(BlueprintPure, Category = "ReactionalMusic|Dev")
	static bool GetParameterValueAsBool(const FReactionalParameterValue& ParameterValue, bool& bWasSuccessful);

	static int32 FindControl(int Id, FString ControlName);
	static int32 FindParameter(int Id, FString ParamName);
	
	static FString GetParameterAsString(int trackthemeId, FString ParamName, bool& bValid);
	static float GetParameterAsFloat(int trackthemeId, FString ParamName, bool& bValid);
	static int32 GetParameterAsInt(int trackthemeId, FString ParamName, bool& bValid);
	static bool GetParameterAsBool(int trackthemeId, FString ParamName, bool& bValid);
};
