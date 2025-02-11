/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "Stats/Stats.h"
#include "Logging//LogMacros.h"
#include "HAL/CriticalSection.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "../../ReactionalThirdPartyLib/reactional.h"
#include "Engine/DataAsset.h"
#include "LatentActions.h" // may be grayed out, but needed for non Unity build

#include "ReactionalEngine.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogReactionalMusic, Log, All);

#define REACTIONAL_LOG(Message, ...)		 UE_LOG(LogReactionalMusic, Log,     TEXT("%hs :: " Message), __func__, ##__VA_ARGS__)
#define REACTIONAL_LOG_WARNING(Message, ...) UE_LOG(LogReactionalMusic, Warning, TEXT("%hs :: " Message), __func__, ##__VA_ARGS__)
#define REACTIONAL_LOG_ERROR(Message, ...)   UE_LOG(LogReactionalMusic, Error,   TEXT("%hs :: " Message), __func__, ##__VA_ARGS__)

static int ReactionalLogCallback(const char* Message, const int _) { REACTIONAL_LOG("%hs", Message) return 0; }

DECLARE_DELEGATE_FiveParams(FNoteOnEvent, double /*offset*/, int32 /*sink*/, int32 /*lane*/, float /*pitch*/, float /*velocity*/);
DECLARE_DELEGATE_FiveParams(FNoteOffEvent, double, int32, int32, float, float);
//DECLARE_DELEGATE_ThreeParams(FStingerEvent, double /*offset*/, bool /*startevent*/, int /*stingerOrigin*/);
DECLARE_DELEGATE(FAudioEndEvent);
DECLARE_DELEGATE_ThreeParams(FBarBeatEvent, double /*offset*/, int32 /*bar*/, int32 /*beat*/);
DECLARE_DELEGATE(FPartEvent);
DECLARE_DYNAMIC_DELEGATE(FReactionalQuantizationEvent);

UENUM(BlueprintType)
enum class EReactionalParameterType : uint8
{
	ParameterType_Bool,
	ParameterType_Int,
	ParameterType_Float,
	ParameterType_String,
	ParameterType_Trigger,
	ParameterType_Invalid
};

UENUM(BlueprintType)
enum class EReactionalQuantizationValue : uint8
{
	WholeNote,
	HalfNote,
	QuarterNote,
	EighthNote,
	SixteenthNote,
	
	DottedWholeNote,
	DottedHalfNote,
	DottedQuarterNote,
	DottedEighthNote,
	DottedSixteenthNote,

	WholeTriplet,
	HalfNoteTriplet,
	QuarterNoteTriplet,
	EighthNoteTriplet,
	SixteenthNoteTriplet,

	Instant,
	
	Count UMETA(Hidden)
};

inline double QuantToDouble(const EReactionalQuantizationValue Quant)
{
	switch (Quant) {
	case EReactionalQuantizationValue::WholeNote:			 { return 1;	  }
	case EReactionalQuantizationValue::HalfNote:			 { return .5;	  }
	case EReactionalQuantizationValue::QuarterNote:			 { return .25;	  }
	case EReactionalQuantizationValue::EighthNote:			 { return .125;	  }
	case EReactionalQuantizationValue::SixteenthNote:		 { return .0625;  }
		
	case EReactionalQuantizationValue::DottedWholeNote:		 { return 1.5;	  } 
	case EReactionalQuantizationValue::DottedHalfNote:		 { return .75;	  } 
	case EReactionalQuantizationValue::DottedQuarterNote:	 { return .375;	  }
	case EReactionalQuantizationValue::DottedEighthNote:	 { return .1875;  }
	case EReactionalQuantizationValue::DottedSixteenthNote:  { return .09375; }

	case EReactionalQuantizationValue::WholeTriplet:		 { return 1.33333333333; }
	case EReactionalQuantizationValue::HalfNoteTriplet:		 { return 0.66666666666; }
	case EReactionalQuantizationValue::QuarterNoteTriplet:	 { return 0.33333333333; }
	case EReactionalQuantizationValue::EighthNoteTriplet:	 { return 0.16666666666; }
	case EReactionalQuantizationValue::SixteenthNoteTriplet: { return 0.08333333333; }
		
	case EReactionalQuantizationValue::Instant:				 { return 0; }
	default: return -1;
	}
}

UENUM(BlueprintType)
enum class EReactionalMusicSystemPlaybackState : uint8
{
	Stopped = 0,
	Playing = 1,
	Paused  = 2
};

namespace Reactional
{
	struct FEventNoteParams
	{
		FEventNoteParams() {}
		FEventNoteParams(float InOffset, int32 InSink, int32 InLane, float InPitch, float InVelocity, bool bInParamsSourceNoteOn, bool bInParamsValid )
			: offset(InOffset)
			, sink(InSink)
			, lane(InLane)
			, pitch(InPitch)
			, velocity(InVelocity)
			, bParamsSourceNoteOn(bInParamsSourceNoteOn)
			, bParamsValid(bInParamsValid)
		{}

		float offset { 0.0f };
		int32 sink { 0 };
		int32 lane { 0 };
		float pitch { 0.0f };
		float velocity { 0.0f };

		FGuid NoteEventGuid;

		double reactional_engine_beats_at_poll { 0.0f };
		double reactional_engine_frames_at_poll { 0.0f };
		double reactional_engine_time_at_poll { 0.0f };
		double reactional_engine_beats_at_trigger { 0.0f };
		double reactional_engine_frames_at_trigger { 0.0f };
		double reactional_engine_time_at_trigger { 0.0f };
		
		bool bParamsSourceNoteOn = false;
		bool bParamsValid = false;
	};

	struct FEventBarBeatParams
	{
		FEventBarBeatParams() {}
		FEventBarBeatParams(float InOffset, int32 InBar, int32 InBeat, bool bInParamsValid)
			: offset(InOffset)
			, bar(InBar)
			, beat(InBeat)
			, bParamsValid(bInParamsValid)
		{}

		float offset { 0.0f };
		int32 bar { 0 };
		int32 beat { 0 };

		FGuid BarBeatEventGuid;

		double reactional_engine_beats_at_poll { 0.0f };
		double reactional_engine_frames_at_poll { 0.0f };
		double reactional_engine_time_at_poll { 0.0f };
		double reactional_engine_beats_at_trigger { 0.0f };
		double reactional_engine_frames_at_trigger { 0.0f };
		double reactional_engine_time_at_trigger { 0.0f };

		bool bParamsValid = false;
	};

	struct FEventStingerParams
	{
		FEventStingerParams() {}
		FEventStingerParams(float InOffset, bool InStartEvent, int32 InStingerOrigin, bool bInParamsValid)
			: offset(InOffset)
			, startevent(InStartEvent)
			, stingerorigin(InStingerOrigin)
			, bParamsValid(bInParamsValid)
		{}

		float offset { 0.0f };
		bool startevent { false };
		int32 stingerorigin { 0 };

		FGuid StingerEventGuid;

		double reactional_engine_beats_at_poll { 0.0f };
		double reactional_engine_frames_at_poll { 0.0f };
		double reactional_engine_time_at_poll { 0.0f };
		double reactional_engine_beats_at_trigger { 0.0f };
		double reactional_engine_frames_at_trigger { 0.0f };
		double reactional_engine_time_at_trigger { 0.0f };

		bool bParamsValid = false;
	};

	struct FOSCValue
	{
		FString TypeTagCode{ TEXT("?") };

		int32 i { 0 };
		float f { 0.0f };
		FString s { TEXT("") };
		FString capital_S { TEXT("") };
		TArray<uint8> b;
		int64_t h { 0 };
		uint64_t t { 0 };
		double d { 0.0 };
		char c { 0 };
		uint32_t r { 0 };
		uint8 m[4];
		bool TF { false };

		FOSCValue()
		{
			m[0] = 0; m[1] = 0; m[2] = 0; m[3] = 0;
		}

		bool IsValueValid() const { return !TypeTagCode.Equals(TEXT("?")); }
	};

	struct FOSCMessage
	{
		FString Address { TEXT("?") };
		FString TypeTag { TEXT("?") };

		TArray<Reactional::FOSCValue> Values;

		int32 Decode(const void* OscData, int32 OscSize, int maxValues = 16);
		static int32 FindInvalidValue(const TArray<Reactional::FOSCValue>& ValuesToCheck);
	};
}

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalParameterValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, transient, Category = ReactionalMusic)
	EReactionalParameterType ParamType = EReactionalParameterType::ParameterType_Bool;

	UPROPERTY(transient)
	bool boolValue = false;

	UPROPERTY(transient)
	int32 intValue = 0;

	UPROPERTY(transient)
	float floatValue = 0.0f;

	UPROPERTY(transient)
	FString strValue;
};

USTRUCT(BlueprintType)
struct FReactionalBundle 
{
    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = ReactionalMusic)
    FString BundlePath;

	UPROPERTY(VisibleAnywhere, Category = ReactionalMusic)
    FString BundleManifestString;

	UPROPERTY(VisibleAnywhere, Category = ReactionalMusic)
	TMap<FName, FString> BundleTrackStatus;

	TMap<FName, TArray<uint8>> BundleTrackFilesContent;
};

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalTrackInfo
{
	GENERATED_USTRUCT_BODY()
	bool operator==(const FReactionalTrackInfo& Other) const { return trackHash == Other.trackHash; }

	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	int32 trackID = -1;

	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	FString trackHash;

	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	FString trackName;

	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	bool bPersist { false };
};

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalThemeInfo
{
	GENERATED_USTRUCT_BODY()
	bool operator==(const FReactionalThemeInfo& Other) const { return themeHash == Other.themeHash; }

	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	int32 themeID = -1;

	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	FString themeHash;

	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	FString themeName;
	
	UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
	bool bPersist { false };
};

UCLASS()
class REACTIONALRUNTIME_API UReactionalBundleDataAsset : public UDataAsset 
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = ReactionalMusic)
    FReactionalBundle Bundle;
};

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalControlInfo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
    float CurrentValue { 0.0f };

    UPROPERTY(BlueprintReadWrite, Category = ReactionalMusic)
    FString ControlTypeStr;
};

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalParsedJsonThemesElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	TArray<FString> stringHashValues;
};

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalParsedJsonPlaylistsElement
{
	GENERATED_USTRUCT_BODY()
	bool operator==(const FReactionalParsedJsonPlaylistsElement& Other) const { return parsedPlaylistName == Other.parsedPlaylistName; }

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	FString parsedPlaylistName;

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	TArray<FString> stringHashValues;
};

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalParsedJsonDataElement
{
	GENERATED_USTRUCT_BODY()
	bool operator==(const FReactionalParsedJsonDataElement& Other) const { return stringHashKey == Other.stringHashKey; }

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	FString stringHashKey;

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	TArray<FString> stringHashValues;
};

USTRUCT(BlueprintType)
struct REACTIONALRUNTIME_API FReactionalParsedJsonSectionsElement
{
	GENERATED_USTRUCT_BODY()
	bool operator==(const FReactionalParsedJsonSectionsElement& Other) const { return parsedSectionName == Other.parsedSectionName; }

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	FString parsedSectionName;

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	TArray<FReactionalParsedJsonThemesElement> parsedJsonThemes;

	UPROPERTY(transient, VisibleAnywhere, Category = ReactionalMusic)
	TArray<FReactionalParsedJsonPlaylistsElement> parsedJsonPlaylists;
};

//This thread is responsible for process function if exec in game thread is false
class FReactionalProcessCallTaskRunnable : public FRunnable
{
public:
	FReactionalProcessCallTaskRunnable();

	virtual uint32 Run() override;
	virtual void Exit() override;

	void EnsureCompletion() const;

	TUniquePtr<FRunnableThread> Thread;
	FThreadSafeBool bShouldRun = false;
	FThreadSafeBool bShouldExit = false;

	double dbl_PlatformSecondsStart = -1.0;
	double dbl_PlatformSecondsLast = -1.0;
	int64 int64_PlatformMilliSeconds = -1;
};

UENUM(BlueprintType)
enum class EReactionalRenderMode : uint8
{
	/** Render audio through synth component. */
	ReactionalRenderAudioSynthComponent,
	/** Render audio through custom MetaSound component. */
	ReactionalRenderAudioMetaSounds,
	/** Don't render audio but only process events. */
	ReactionalRenderAudioEventsOnly
};

UENUM(BlueprintType)
enum class EReactionalThreadingMode : uint8
{
	/** Processing of time and events runs in GameThread Tick. */
	GameThread_Tick,
	/** Processing of time and events runs in separate FRunnableThread. */
	DedicatedThread
};

UENUM(BlueprintType)
enum class EReactionalEngineThreadingRenderingState : uint8
{
	UnInitializedState,
	MetasoundRender_DedicatedThreadEventProcessing,
	MetasoundRender_GameThreadEventProcessing,
	SynthComponentRender_DedicatedThreadEventProcessing,
	SynthComponentRender_GameThreadEventProcessing,
	EditorPreview
};

/**
 * Log levels are listed in increasing order.
 * Levels below the selected will also be active.
 */
UENUM()
enum class EReactionalLogLevel : uint8
{
	/** No logging at all. */
	None	 = 0,
	/** Only critical errors are logged. */
	Critical = 1, 
	/** Any error that was unexpected, such as out of memory, invalid file io etc */
	Error	 = 2,
	/** Expected errors, such as file not found, invalid json, etc. */
	Warning  = 3,
	/** General information, not too verbose. */
	Info	 = 4,
	/** Debug information, verbose. */
	Debug	 = 5, 
};

// Returns both an engine pointer and reactional c lib pointer (called engine and lib_ptr respectively)
#define REACTIONAL_GET_LIB_PTR_OR_RETURN(value) \
	[[maybe_unused]] struct FReactionalEngine* engine = FReactionalEngine::GetEngine();\
	if (engine == nullptr) { /*REACTIONAL_LOG_ERROR("Failed to get engine.")*/ return value; }\
	[[maybe_unused]] void* lib_ptr = engine->reactionallib_ptr();\
	if (lib_ptr == nullptr) { /*REACTIONAL_LOG_ERROR("Failed to get internal library pointer.")*/ return value; }
	
class UReactionalSubsystem;

//TSharedFromThis not needed, we call MakeSharedInstance when a shared pointer is needed 
struct FReactionalEngine
{
public:
	static FReactionalEngine* GetEngine() { return InstanceWeakPtr.Pin().Get(); }
	
	UReactionalSubsystem* GetSubsystem() const { return ReactionalSubsystemWeakPtr.Get(); }
	
	void* reactionallib_ptr() const
	{
		if(!ReactionalUniquePtr.IsValid()) { return nullptr; }
		return ReactionalUniquePtr.Get()->voidptr;
	}
	
	static TSharedPtr<FReactionalEngine> MakeSharedInstance();
	
	//________________
	// Task Runnable

	TUniquePtr<FReactionalProcessCallTaskRunnable> ReactionalProcessCallTask;
	
	EReactionalEngineThreadingRenderingState EngineThreadingRenderingState;

	bool ThreadingRenderingStateIsDedicatedRunning() const;
	bool ThreadingRenderingStateIsGameThreadRunning() const;

	void CreateDedicatedThread();
	void StopDedicatedThread() const;
	void BindStaticDelegates();
	
	//________________
	// Events

	TArray<Reactional::FEventNoteParams> EventNotesDeferredList;
	TArray<Reactional::FEventNoteParams> MetasoundEventNotesDeferredList;
	
	TArray<Reactional::FEventBarBeatParams> EventBarBeatDeferredList;

	TArray<Reactional::FEventStingerParams> EventStingerDeferredList;

	FNoteOnEvent NoteOnEventStaticDelegate;
	FNoteOffEvent NoteOffEventStaticDelegate;
	FAudioEndEvent AudioEndEventStaticDelegate;
	FBarBeatEvent BarBeatEventStaticDelegate;
	FPartEvent PartEventStaticDelegate;

	void Event_NoteOn_Dispatch(double offset, int32 sink, int32 lane, float pitch, float velocity);
	void Event_NoteOff_Dispatch(double offset, int32 sink, int32 lane, float pitch, float velocity);
	void Event_Stinger_Dispatch(double offset, bool startevent, int32 stingerOrigin);
	void Event_AudioEnd_Dispatch() const;
	void Event_BarBeatEvent_Dispatch(double offset, int32 bar, int32 beat);
	void Event_PartEvent_Dispatch() const;

	void GetEvents(int trackid);
	void EventPoll(int id, int64_t& startBeat, TArray<Reactional::FOSCMessage>& OutEventMessages, int maxMessages = 0) const;

	TArray<Reactional::FOSCMessage> OSCEventMessages;

	//________________
	// MetaSound

	//Used as temp buffer for TArrayView if offset and sink are the same
	TArray<float> MetaSoundEventNoteSharedTempFloatValues;
	TArray<int32> MetaSoundEventNoteSharedTempIntValues;

	TArray<float> MetaSoundEventNoteOffsetValues;
	TArray<int32> MetaSoundEventNoteSinkValues;
	TArray<int32> MetaSoundEventNoteLaneValues;
	TArray<float> MetaSoundEventNotePitchValues;
	TArray<float> MetaSoundEventNoteVelocityValues;

	TMap<FGuid, int32> MetasoundEventNoteIndexInArrayMap;

	TArrayView<float> MetasoundGetEventNoteViewOffset(double currentBeat, const FGuid Guid, const int32 SinkFilter = -1);
	TArrayView<int32> MetasoundGetEventNoteViewSink(double currentBeat, const FGuid Guid, const int32 SinkFilter = -1);
	TArrayView<int32> MetasoundGetEventNoteViewLane(double currentBeat, const FGuid Guid, const int32 SinkFilter = -1);
	TArrayView<float> MetasoundGetEventNoteViewPitch(double currentBeat, const FGuid Guid, const int32 SinkFilter = -1);
	TArrayView<float> MetasoundGetEventNoteViewVelocity(double currentBeat, const FGuid Guid, const int32 SinkFilter = -1);

	FCriticalSection DeferredEventsCS;
	FCriticalSection MetasoundEventsTriggerCS;
	FCriticalSection DedicatedThreadProcessCS;
	
	//________________
	// Misc

	// markus:
	//	here if we want global lookahead (and other similar vars)
	//	should be atomic only if It is queried from Async task of Engine process

	std::atomic<bool> _allowPlay { false };
	std::atomic<int32> _currentRootNode;

	~FReactionalEngine();

	//TWeakObjectPtr<class AReactionalInstManagerActor> ReactionalInstActorWeakPtr;
	TWeakObjectPtr<UReactionalSubsystem> ReactionalSubsystemWeakPtr;
	
private:
	//TUniquePtr template does not like void type, so we wrap it
	struct FReactionalLibPtr
	{
		FReactionalLibPtr() = delete;
		FReactionalLibPtr(void *Inptr) : voidptr(Inptr) {}
		
		void* voidptr = nullptr;
	};

	TUniquePtr<FReactionalLibPtr> ReactionalUniquePtr;

	FReactionalEngine() = default;
	static TWeakPtr<FReactionalEngine> InstanceWeakPtr;
};
