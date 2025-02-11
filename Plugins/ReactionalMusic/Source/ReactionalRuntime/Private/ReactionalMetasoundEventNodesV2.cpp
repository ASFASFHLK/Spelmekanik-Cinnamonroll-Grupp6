/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "Internationalization/Text.h"
#include "MetasoundExecutableOperator.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundNodeRegistrationMacro.h"
#include "MetasoundAudioBuffer.h"
#include "MetasoundPrimitives.h"
#include "MetasoundFacade.h"
#include "MetasoundParamHelper.h"
#include "MetasoundOperatorSettings.h"
#include "MetasoundDataTypeRegistrationMacro.h"
#include "ReactionalMetasoundTypes.h"
#include "ReactionalBPLibrary.h"
#include "ReactionalSubsystem.h"

#define LOCTEXT_NAMESPACE "ReactionalMetasound"

REGISTER_METASOUND_DATATYPE(Reactional::FMetasoundTestParams, "ReactionalTestParams", Metasound::ELiteralType::FloatArray)

namespace Metasound
{
	namespace ReactionalVertexNames
	{
		METASOUND_PARAM(InputNoteEventSinkFilter, "Sink Equal To", "Filter based on sink value");
		METASOUND_PARAM(OutputNoteEventArray1, "Offset", "");
		METASOUND_PARAM(OutputNoteEventArray2, "Sink", "");
		METASOUND_PARAM(OutputNoteEventArray3, "Lane", "");
		METASOUND_PARAM(OutputNoteEventArray4, "Pitch", "");
		METASOUND_PARAM(OutputNoteEventArray5, "Velocity", "");
		METASOUND_PARAM(OutputBeat, "Beat", "Beat");
		METASOUND_PARAM(OutputNotesNum, "Event Notes Num", "Number of note events in frame");
	}

	using namespace ReactionalVertexNames;

	// Operator Class
	//TODO Template this
	class FReactionalEventNoteOnArrayOperator : public TExecutableOperator<FReactionalEventNoteOnArrayOperator>
	{
	public:
		using FArrayFloatNoteEventWriteRef = TDataWriteReference<TArray<float>>;
		using NoteEventArrayFloatType = TArray<float>;
		using FArrayIntNoteEventWriteRef = TDataWriteReference<TArray<int32>>;
		using NoteEventArrayIntType = TArray<int32>;

		FReactionalEventNoteOnArrayOperator(const FBuildOperatorParams& InParams, const FInt32ReadRef& InSinqEqualToReadRef)
			: SinkEqualToFilter(InSinqEqualToReadRef)
			, TriggerOnNoteOn(FTriggerWriteRef::CreateNew(InParams.OperatorSettings))
			, NoteEventArrayOffsetOutput(FArrayFloatNoteEventWriteRef::CreateNew())
			, NoteEventArraySinkOutput(FArrayIntNoteEventWriteRef::CreateNew())
			, NoteEventArrayLaneOutput(FArrayIntNoteEventWriteRef::CreateNew())
			, NoteEventArrayPitchOutput(FArrayFloatNoteEventWriteRef::CreateNew())
			, NoteEventArrayVelocityOutput(FArrayFloatNoteEventWriteRef::CreateNew())
			, BeatOutput(FFloatWriteRef::CreateNew())
			, NumNotesOutput(FInt32WriteRef::CreateNew())
			, OperatorSettings(InParams.OperatorSettings)
		{}

		static const FNodeClassMetadata& GetNodeInfo()
		{
			static const FNodeClassMetadata Metadata {
				.ClassName         = FNodeClassName { "Reactional", "ReactionalEventNoteOnArray", FName() },
				.MajorVersion      = 1,
				.MinorVersion      = 0,
				.DisplayName       = METASOUND_LOCTEXT("ReactionalEventNoteOnArrayDisplayName", "Reactional Music | EventNoteOnTrigger V2"),
				.Description       = METASOUND_LOCTEXT("ReactionalEventNoteOnArrayDesc", "Event Callback from the Reactional engine."),
				.Author            = PluginAuthor,
				.PromptIfMissing   = PluginNodeMissingPrompt,
				.DefaultInterface  = DeclareVertexInterface(),
				.CategoryHierarchy = { NodeCategories::Functions },
				.Keywords          = {},
				.DisplayStyle      = FNodeDisplayStyle {}
			};
			return Metadata;
		}

		static const FVertexInterface& DeclareVertexInterface()
		{
			using namespace ReactionalVertexNames;

			static const FVertexInterface Interface(
				FInputVertexInterface(
					TInputDataVertex<int32>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputNoteEventSinkFilter), -1)
				),
				FOutputVertexInterface(
					TOutputDataVertex<FTrigger>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputTriggerOnNoteOn)),
					TOutputDataVertex<NoteEventArrayFloatType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray1)),
					TOutputDataVertex<NoteEventArrayIntType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray2)),
					TOutputDataVertex<NoteEventArrayIntType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray3)),
					TOutputDataVertex<NoteEventArrayFloatType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray4)),
					TOutputDataVertex<NoteEventArrayFloatType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray5)),
					TOutputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputBeat)),
					TOutputDataVertex<int32>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNotesNum))
				)
			);
			return Interface;
		}

		virtual ~FReactionalEventNoteOnArrayOperator() = default;

		virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override
		{
			using namespace ReactionalVertexNames;
		
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputNoteEventSinkFilter), SinkEqualToFilter);
		}

		virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override
		{
			using namespace ReactionalVertexNames;

			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputTriggerOnNoteOn), TriggerOnNoteOn);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray1), NoteEventArrayOffsetOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray2), NoteEventArraySinkOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray3), NoteEventArrayLaneOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray4), NoteEventArrayPitchOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray5), NoteEventArrayVelocityOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputBeat), BeatOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNotesNum), NumNotesOutput);
		}

		virtual FDataReferenceCollection GetInputs() const override
		{
			//checkNoEntry();
			return {};
		}

		virtual FDataReferenceCollection GetOutputs() const override
		{
			//checkNoEntry();
			return {};
		}

		static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)
		{
			using namespace ReactionalVertexNames;

			if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false) &&
				FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds)
			{
				//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation
				TSharedRef<FReactionalEngine, ESPMode::ThreadSafe> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

				bReactionalMetaSoundsValid = true;
				currentBeatInstantiation = UReactionalBPLibrary::GetCurrentBeatAsDouble();
				currentBeatFirstRender = -1.0f;
			}
			else
			{
				bReactionalMetaSoundsValid = false;
			}

			const FInputVertexInterface& InputInterface = InParams.Node.GetVertexInterface().GetInputInterface();
			const FDataReferenceCollection& InputCollection = InParams.InputData.ToDataReferenceCollection();

			FInt32ReadRef InSinkReadRef = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<int32>(InputInterface, METASOUND_GET_PARAM_NAME(InputNoteEventSinkFilter), InParams.OperatorSettings);

			return MakeUnique<FReactionalEventNoteOnArrayOperator>(InParams, InSinkReadRef);
		}

        int32 accumulated_frames = 0;
        
		void Execute()
		{
			float blockRate = OperatorSettings.GetTargetBlockRate();
			float actualblockRate = OperatorSettings.GetActualBlockRate();
			float sampleRate = OperatorSettings.GetSampleRate();

			int32 framesPerBlock = OperatorSettings.GetNumFramesPerBlock();

			if (bReactionalMetaSoundsValid)
			{
				if (currentBeatFirstRender < 0.0)
				{
					if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false))
					{
						//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation
						TSharedRef<FReactionalEngine, ESPMode::ThreadSafe> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

						currentBeatFirstRender = UReactionalBPLibrary::GetCurrentBeatAsDouble();
						currentFrameFirstRender = reactional_get_frames_from_beats(FReactionalEngine::GetEngine()->reactionallib_ptr(), 0, currentBeatFirstRender);

						TimecyclesFirstRender = FPlatformTime::Cycles64();
						TimeFirstRender = static_cast<double>(TimecyclesFirstRender) * FPlatformTime::GetSecondsPerCycle64();
					}
				}
				
				if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false))
				{
					//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation
					TSharedRef<FReactionalEngine, ESPMode::ThreadSafe> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

					double currentBeat = UReactionalBPLibrary::GetCurrentBeatAsDouble();
					double currentFrame = reactional_get_frames_from_beats(FReactionalEngine::GetEngine()->reactionallib_ptr(), 0, currentBeat);

					const int32& sinkfilter = *SinkEqualToFilter; 

					if (FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList.Num() > 0)
					{
						FScopeLock Lock(&FReactionalEngine::GetEngine()->MetasoundEventsTriggerCS);

						TArray<int32> NodeIdxToRemove;
						TArray<int32> NodeIdxToTrigger;
						TMap<FGuid, int32> NodeIdxToFramesMap;
						//TMap<int32, int32> NodeIdxToFramesMap;

						for (int32 nodeIdx = 0; nodeIdx < FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList.Num(); nodeIdx++)
						{
							Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[nodeIdx];
							if (noteParams.offset <= currentBeat && noteParams.bParamsSourceNoteOn && noteParams.bParamsValid && (sinkfilter < 0 || noteParams.sink == sinkfilter))
							{
								NodeIdxToTrigger.AddUnique(nodeIdx);
								NodeIdxToRemove.AddUnique(nodeIdx);
								NodeIdxToFramesMap.FindOrAdd(noteParams.NoteEventGuid, accumulated_frames);
							}
						}

						if (NodeIdxToTrigger.Num() > 0)
						{
							if ( NodeIdxToTrigger.Num() > 1)
							{
								int32 firstIdx = std::numeric_limits<int32>::max();

								TArray<float> Offset;
								TArray<int32> Sink;
								TArray<int32> Lane;
								TArray<float> Pitch;
								TArray<float> Velocity;

								//more than one
								for (int32 Idx = 0; Idx < NodeIdxToTrigger.Num(); Idx++)
								{
									Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[NodeIdxToTrigger[Idx]];
									Offset.Add(noteParams.offset);
									Sink.Add(noteParams.sink);
									Lane.Add(noteParams.lane);
									Pitch.Add(noteParams.pitch);
									Velocity.Add(noteParams.velocity);
								}

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Append(Offset);
								TArrayView<float> TAVflOffset(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.GetData() + firstIdx, Offset.Num());
								*NoteEventArrayOffsetOutput = TAVflOffset;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Append(Sink);
								TArrayView<int32> TAVintSink(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.GetData() + firstIdx, Sink.Num());
								*NoteEventArraySinkOutput = TAVintSink;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Append(Lane);
								TArrayView<int32> TAVintLane(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.GetData() + firstIdx, Lane.Num());
								*NoteEventArrayLaneOutput = TAVintLane;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Append(Pitch);
								TArrayView<float> TAVflPitch(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.GetData() + firstIdx, Pitch.Num());
								*NoteEventArrayPitchOutput = TAVflPitch;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Append(Velocity);
								TArrayView<float> TAVflVelocity(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.GetData() + firstIdx, Velocity.Num());
								*NoteEventArrayVelocityOutput = TAVflVelocity;
								
								*NumNotesOutput = NodeIdxToTrigger.Num();
							}
							else
							{
								Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[NodeIdxToTrigger[0]];
								*NoteEventArrayOffsetOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewOffset(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArraySinkOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewSink(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArrayLaneOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewLane(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArrayPitchOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewPitch(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArrayVelocityOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewVelocity(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								
								*NumNotesOutput = 1;
							}

							*BeatOutput = (float)currentBeat;

							if (!TriggerOnNoteOn->IsTriggeredInBlock())
							{
								Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[NodeIdxToTrigger[0]];
								//TriggerOnNoteOn->TriggerFrame(NodeIdxToFramesMap.FindChecked(NodeIdxToTrigger[0]));
								//TriggerOnNoteOn->TriggerFrame(NodeIdxToFramesMap.FindChecked(noteParams.NoteEventGuid));
								TriggerOnNoteOn->TriggerFrame(NodeIdxToFramesMap.FindChecked(noteParams.NoteEventGuid));
								//TriggerOnNoteOn->TriggerFrame(FMath::RandRange(0, framesPerBlock));
							}
						}
						if (NodeIdxToRemove.Num() > 0)
						{
							for (int32 Idx = NodeIdxToRemove.Num()-1; Idx >= 0; Idx--)
							{
								FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList.RemoveAt(NodeIdxToRemove[Idx]);
							}
						}
					}
					TriggerOnNoteOn->AdvanceBlock();
                    accumulated_frames = framesPerBlock;
				}
			}
		}

	private:

		// input pins

		FInt32ReadRef SinkEqualToFilter;

		// output pins
		
		FTriggerWriteRef TriggerOnNoteOn;
		FArrayFloatNoteEventWriteRef NoteEventArrayOffsetOutput;
		FArrayIntNoteEventWriteRef NoteEventArraySinkOutput;
		FArrayIntNoteEventWriteRef NoteEventArrayLaneOutput;
		FArrayFloatNoteEventWriteRef NoteEventArrayPitchOutput;
		FArrayFloatNoteEventWriteRef NoteEventArrayVelocityOutput;
		FFloatWriteRef BeatOutput;
		FInt32WriteRef NumNotesOutput;
		//TDataWriteReference<int32> OutputValue;

		const FOperatorSettings OperatorSettings;

		static bool bReactionalMetaSoundsValid;
		
		//remove, rewrite as they are static variables and should be per node.
		static double currentBeatInstantiation;
		static double currentFrameInstantiation;
		static double currentBeatFirstRender;
		static double currentFrameFirstRender;

		static uint64 TimecyclesInstantiation;
		static double TimeInstantation;
		static uint64 TimecyclesFirstRender;
		static double TimeFirstRender;

		//remove, rewrite as they are static variables and should be per node.
	};

	bool FReactionalEventNoteOnArrayOperator::bReactionalMetaSoundsValid = false;

	double FReactionalEventNoteOnArrayOperator::currentBeatInstantiation  = std::numeric_limits<double>::max();
	double FReactionalEventNoteOnArrayOperator::currentFrameInstantiation = std::numeric_limits<double>::max();
	uint64 FReactionalEventNoteOnArrayOperator::TimecyclesInstantiation   = std::numeric_limits<int64>::max();
	double FReactionalEventNoteOnArrayOperator::TimeInstantation		  = std::numeric_limits<double>::max();

	double FReactionalEventNoteOnArrayOperator::currentBeatFirstRender    = std::numeric_limits<double>::max();
	double FReactionalEventNoteOnArrayOperator::currentFrameFirstRender   = std::numeric_limits<double>::max();
	uint64 FReactionalEventNoteOnArrayOperator::TimecyclesFirstRender     = std::numeric_limits<int64>::max();
	double FReactionalEventNoteOnArrayOperator::TimeFirstRender			  = std::numeric_limits<double>::max();

	// Node Classes
	class FReactionalEventNoteOnArrayNode : public FNodeFacade
	{
	public:
		FReactionalEventNoteOnArrayNode(const FNodeInitData& InitData)
			: FNodeFacade(InitData.InstanceName, InitData.InstanceID, TFacadeOperatorClass<FReactionalEventNoteOnArrayOperator>())
		{
		}
	};

	// Register node
	METASOUND_REGISTER_NODE(FReactionalEventNoteOnArrayNode)

	// Operator Class
	//TODO template this
	class FReactionalEventNoteOffArrayOperator : public TExecutableOperator<FReactionalEventNoteOffArrayOperator>
	{
	public:
		using FArrayFloatNoteEventWriteRef = TDataWriteReference<TArray<float>>;
		using NoteEventArrayFloatType = TArray<float>;
		using FArrayIntNoteEventWriteRef = TDataWriteReference<TArray<int32>>;
		using NoteEventArrayIntType = TArray<int32>;
		
		FReactionalEventNoteOffArrayOperator(const FBuildOperatorParams& InParams, const FInt32ReadRef& InSinqEqualToReadRef)
			: SinkEqualToFilter(InSinqEqualToReadRef)
			, TriggerOnNoteOff(FTriggerWriteRef::CreateNew(InParams.OperatorSettings))
			, NoteEventArrayOffsetOutput(FArrayFloatNoteEventWriteRef::CreateNew())
			, NoteEventArraySinkOutput(FArrayIntNoteEventWriteRef::CreateNew())
			, NoteEventArrayLaneOutput(FArrayIntNoteEventWriteRef::CreateNew())
			, NoteEventArrayPitchOutput(FArrayFloatNoteEventWriteRef::CreateNew())
			, NoteEventArrayVelocityOutput(FArrayFloatNoteEventWriteRef::CreateNew())
			, BeatOutput(FFloatWriteRef::CreateNew())
			, NumNotesOutput(FInt32WriteRef::CreateNew())
			, OperatorSettings(InParams.OperatorSettings)
		{}

		static const FNodeClassMetadata& GetNodeInfo()
		{
			auto CreateNodeClassMetadata = []() -> FNodeClassMetadata
				{
					FVertexInterface NodeInterface = DeclareVertexInterface();

					FNodeClassMetadata Metadata
					{
						FNodeClassName { "Reactional", "ReactionalEventNoteOffArray", FName() },
						1, // Major Version
						0, // Minor Version
						METASOUND_LOCTEXT("ReactionalEventNoteOffArrayDisplayName", "Reactional Music | EventNoteOffTrigger V2"),
						METASOUND_LOCTEXT("ReactionalEventNoteOffArrayDesc", "Event Callback from the Reactional engine."),
						PluginAuthor,
						PluginNodeMissingPrompt,
						NodeInterface,
						{ NodeCategories::Functions},
						{ },
						FNodeDisplayStyle{}
					};
					return Metadata;
				};

			static const FNodeClassMetadata Metadata = CreateNodeClassMetadata();
			return Metadata;
		}

		static const FVertexInterface& DeclareVertexInterface()
		{
			using namespace ReactionalVertexNames;

			static const FVertexInterface Interface(
				FInputVertexInterface(
					TInputDataVertex<int32>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputNoteEventSinkFilter), -1)
				),
				FOutputVertexInterface(
					TOutputDataVertex<FTrigger>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputTriggerOnNoteOff)),
					TOutputDataVertex<NoteEventArrayFloatType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray1)),
					TOutputDataVertex<NoteEventArrayIntType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray2)),
					TOutputDataVertex<NoteEventArrayIntType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray3)),
					TOutputDataVertex<NoteEventArrayFloatType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray4)),
					TOutputDataVertex<NoteEventArrayFloatType>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNoteEventArray5)),
					TOutputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputBeat)),
					TOutputDataVertex<int32>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputNotesNum))
				)
			);
			return Interface;
		}

		virtual ~FReactionalEventNoteOffArrayOperator() = default;

		virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override
		{
			using namespace ReactionalVertexNames;

			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputNoteEventSinkFilter), SinkEqualToFilter);
		}

		virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override
		{
			using namespace ReactionalVertexNames;

			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputTriggerOnNoteOff), TriggerOnNoteOff);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray1), NoteEventArrayOffsetOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray2), NoteEventArraySinkOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray3), NoteEventArrayLaneOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray4), NoteEventArrayPitchOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNoteEventArray5), NoteEventArrayVelocityOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputBeat), BeatOutput);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputNotesNum), NumNotesOutput);
		}

		virtual FDataReferenceCollection GetInputs() const override
		{
			//checkNoEntry();
			return {};
		}

		virtual FDataReferenceCollection GetOutputs() const override
		{
			//checkNoEntry();
			return {};
		}

		static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)
		{
			using namespace ReactionalVertexNames;

			if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false))
			{
				//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation
				TSharedRef<FReactionalEngine, ESPMode::ThreadSafe> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

				if (FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds)
				{
					bReactionalMetaSoundsValid = true;
					currentBeatInstantiation = UReactionalBPLibrary::GetCurrentBeatAsDouble();
					currentBeatFirstRender = -1.0f;
				}
				else
				{
					bReactionalMetaSoundsValid = false;
				}
			}

			const FInputVertexInterface& InputInterface = InParams.Node.GetVertexInterface().GetInputInterface();
			const FDataReferenceCollection& InputCollection = InParams.InputData.ToDataReferenceCollection();

			FInt32ReadRef InSinkReadRef = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<int32>(InputInterface, METASOUND_GET_PARAM_NAME(InputNoteEventSinkFilter), InParams.OperatorSettings);

			return MakeUnique<FReactionalEventNoteOffArrayOperator>(InParams, InSinkReadRef);
		}

        int32 accumulated_frames = 0;

		void Execute()
		{
			float blockRate = OperatorSettings.GetTargetBlockRate();
			float actualblockRate = OperatorSettings.GetActualBlockRate();
			float sampleRate = OperatorSettings.GetSampleRate();

			int32 framesPerBlock = OperatorSettings.GetNumFramesPerBlock();
			
			if (bReactionalMetaSoundsValid)
			{
				if (currentBeatFirstRender < 0.0)
				{
					if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false))
					{
						//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation
						TSharedRef<FReactionalEngine, ESPMode::ThreadSafe> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

						currentBeatFirstRender = UReactionalBPLibrary::GetCurrentBeatAsDouble();
						currentFrameFirstRender = reactional_get_frames_from_beats(FReactionalEngine::GetEngine()->reactionallib_ptr(), 0, currentBeatFirstRender);

						TimecyclesFirstRender = FPlatformTime::Cycles64();
						TimeFirstRender = static_cast<double>(TimecyclesFirstRender) * FPlatformTime::GetSecondsPerCycle64();
					}
				}

				if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false))
				{
					//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation
					TSharedRef<FReactionalEngine, ESPMode::ThreadSafe> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

					double currentBeat = UReactionalBPLibrary::GetCurrentBeatAsDouble();
					double currentFrame = reactional_get_frames_from_beats(FReactionalEngine::GetEngine()->reactionallib_ptr(), 0, currentBeat);

					const int32& sinkfilter = *SinkEqualToFilter;

					if (FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList.Num() > 0)
					{
						FScopeLock Lock(&FReactionalEngine::GetEngine()->MetasoundEventsTriggerCS);

						TArray<int32> NodeIdxToRemove;
						TArray<int32> NodeIdxToTrigger;
						TMap<FGuid, int32> NodeIdxToFramesMap;

						for (int32 nodeIdx = 0; nodeIdx < FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList.Num(); nodeIdx++)
						{
							Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[nodeIdx];
							if (noteParams.offset <= currentBeat && !noteParams.bParamsSourceNoteOn && noteParams.bParamsValid && (sinkfilter < 0 || noteParams.sink == sinkfilter))
							{
								NodeIdxToTrigger.AddUnique(nodeIdx);
								NodeIdxToRemove.AddUnique(nodeIdx);
								NodeIdxToFramesMap.FindOrAdd(noteParams.NoteEventGuid, accumulated_frames);
							}
						}

						if (NodeIdxToTrigger.Num() > 0)
						{
							if (NodeIdxToTrigger.Num() > 1)
							{
								int32 firstIdx = std::numeric_limits<int32>::max();

								TArray<float> Offset;
								TArray<int32> Sink;
								TArray<int32> Lane;
								TArray<float> Pitch;
								TArray<float> Velocity;

								//more than one
								for (int32 Idx = 0; Idx < NodeIdxToTrigger.Num(); Idx++)
								{
									Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[NodeIdxToTrigger[Idx]];
									Offset.Add(noteParams.offset);
									Sink.Add(noteParams.sink);
									Lane.Add(noteParams.lane);
									Pitch.Add(noteParams.pitch);
									Velocity.Add(noteParams.velocity);
								}

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Append(Offset);
								TArrayView<float> TAVflOffset(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.GetData() + firstIdx, Offset.Num());
								*NoteEventArrayOffsetOutput = TAVflOffset;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Append(Sink);
								TArrayView<int32> TAVintSink(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.GetData() + firstIdx, Sink.Num());
								*NoteEventArraySinkOutput = TAVintSink;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.Append(Lane);
								TArrayView<int32> TAVintLane(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempIntValues.GetData() + firstIdx, Lane.Num());
								*NoteEventArrayLaneOutput = TAVintLane;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Append(Pitch);
								TArrayView<float> TAVflPitch(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.GetData() + firstIdx, Pitch.Num());
								*NoteEventArrayPitchOutput = TAVflPitch;

								firstIdx = FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Num();
								FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.Append(Velocity);
								TArrayView<float> TAVflVelocity(FReactionalEngine::GetEngine()->MetaSoundEventNoteSharedTempFloatValues.GetData() + firstIdx, Velocity.Num());
								*NoteEventArrayVelocityOutput = TAVflVelocity;

								*NumNotesOutput = NodeIdxToTrigger.Num();
							}
							else
							{
								Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[NodeIdxToTrigger[0]];
								*NoteEventArrayOffsetOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewOffset(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArraySinkOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewSink(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArrayLaneOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewLane(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArrayPitchOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewPitch(currentBeat, noteParams.NoteEventGuid, sinkfilter);
								*NoteEventArrayVelocityOutput = FReactionalEngine::GetEngine()->MetasoundGetEventNoteViewVelocity(currentBeat, noteParams.NoteEventGuid, sinkfilter);

								*NumNotesOutput = 1;
							}

							*BeatOutput = (float)currentBeat;

							if (!TriggerOnNoteOff->IsTriggeredInBlock())
							{
								Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[NodeIdxToTrigger[0]];
								//TriggerOnNoteOff->TriggerFrame(NodeIdxToFramesMap.FindChecked(NodeIdxToTrigger[0]));
								TriggerOnNoteOff->TriggerFrame(NodeIdxToFramesMap.FindChecked(noteParams.NoteEventGuid));
								//TriggerOnNoteOff->TriggerFrame(FMath::RandRange(0, framesPerBlock));
							}
						}
						if (NodeIdxToRemove.Num() > 0)
						{
							for (int32 Idx = NodeIdxToRemove.Num() - 1; Idx >= 0; Idx--)
							{
								FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList.RemoveAt(NodeIdxToRemove[Idx]);
							}
						}
					}
					TriggerOnNoteOff->AdvanceBlock();
                    accumulated_frames = framesPerBlock;
				}
			}
		}

	private:

		// input pins
		FInt32ReadRef SinkEqualToFilter;

		// output pins
		FTriggerWriteRef TriggerOnNoteOff;
		FArrayFloatNoteEventWriteRef NoteEventArrayOffsetOutput;
		FArrayIntNoteEventWriteRef NoteEventArraySinkOutput;
		FArrayIntNoteEventWriteRef NoteEventArrayLaneOutput;
		FArrayFloatNoteEventWriteRef NoteEventArrayPitchOutput;
		FArrayFloatNoteEventWriteRef NoteEventArrayVelocityOutput;
		FFloatWriteRef BeatOutput;
		FInt32WriteRef NumNotesOutput;
		//TDataWriteReference<int32> OutputValue;

		const FOperatorSettings OperatorSettings;
		
		static bool bReactionalMetaSoundsValid;

		//TODO remove, rewrite as they are static variables and should be per node and probably not needed at all.
		static double currentBeatInstantiation;
		static double currentFrameInstantiation;
		static double currentBeatFirstRender;
		static double currentFrameFirstRender;
		//remove, rewrite as they are static variables and should be per node.

		static uint64 TimecyclesInstantiation;
		static double TimeInstantation;
		static uint64 TimecyclesFirstRender;
		static double TimeFirstRender;
	};

	bool FReactionalEventNoteOffArrayOperator::bReactionalMetaSoundsValid = false;

	double FReactionalEventNoteOffArrayOperator::currentBeatInstantiation = std::numeric_limits<double>::max();
	double FReactionalEventNoteOffArrayOperator::currentFrameInstantiation = std::numeric_limits<double>::max();
	uint64  FReactionalEventNoteOffArrayOperator::TimecyclesInstantiation = std::numeric_limits<int64>::max();
	double FReactionalEventNoteOffArrayOperator::TimeInstantation = std::numeric_limits<double>::max();

	double FReactionalEventNoteOffArrayOperator::currentBeatFirstRender = std::numeric_limits<double>::max();
	double FReactionalEventNoteOffArrayOperator::currentFrameFirstRender = std::numeric_limits<double>::max();
	uint64  FReactionalEventNoteOffArrayOperator::TimecyclesFirstRender = std::numeric_limits<int64>::max();
	double FReactionalEventNoteOffArrayOperator::TimeFirstRender = std::numeric_limits<double>::max();

	// Node Class
	class FReactionalEventNoteOffArrayNode : public FNodeFacade
	{
	public:
		FReactionalEventNoteOffArrayNode(const FNodeInitData& InitData)
			: FNodeFacade(InitData.InstanceName, InitData.InstanceID, TFacadeOperatorClass<FReactionalEventNoteOffArrayOperator>())
		{
		}
	};

	// Register node
	METASOUND_REGISTER_NODE(FReactionalEventNoteOffArrayNode)
}

#undef LOCTEXT_NAMESPACE
