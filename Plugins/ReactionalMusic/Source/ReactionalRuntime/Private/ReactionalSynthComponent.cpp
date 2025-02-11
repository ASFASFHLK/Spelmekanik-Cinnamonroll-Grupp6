/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalSynthComponent.h"

#include "AudioDevice.h"
#include "ReactionalBPLibrary.h"
#include "ReactionalSubsystem.h"

bool UReactionalSynthComponent::Init(int32& SampleRate)
{
	NumChannels = 2;
	sampleRateFromInit = SampleRate;

	return true;
}

void UReactionalSynthComponent::OnRegister()
{
	Super::OnRegister();

	SetComponentTickEnabled(true);
	RegisterComponent();
}

bool UReactionalSynthComponent::IsReadyForFinishDestroy()
{
	if (IsRunningCommandlet() || IsTemplate())
	{
		return Super::IsReadyForFinishDestroy();
	}

	auto* Engine = FReactionalEngine::GetEngine();
	if (!Engine || Engine->EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::SynthComponentRender_GameThreadEventProcessing
				|| Engine->EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::MetasoundRender_GameThreadEventProcessing
				|| !Engine->ReactionalProcessCallTask.Get()
	) {
		return Super::IsReadyForFinishDestroy();
	}

	{
		FScopeLock Lock(&(Engine->DedicatedThreadProcessCS));
		return Super::IsReadyForFinishDestroy();
	}
}

void UReactionalSynthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	REACTIONAL_GET_LIB_PTR_OR_RETURN()

	
	if (engine->ThreadingRenderingStateIsGameThreadRunning())
	{
		int ErrorCode = reactional_process(lib_ptr, -1);
		engine->GetEvents(-1);
	}

	if (engine->EngineThreadingRenderingState != EReactionalEngineThreadingRenderingState::EditorPreview
	 && engine->EngineThreadingRenderingState != EReactionalEngineThreadingRenderingState::UnInitializedState
	) {
		double currentBeat = UReactionalBPLibrary::GetCurrentBeatAsDouble();
		double currentFrame = reactional_get_frames_from_beats(lib_ptr, 0, currentBeat);
		
		if (engine->EventNotesDeferredList.Num() > 0
		 || engine->EventBarBeatDeferredList.Num() > 0
		 || engine->EventStingerDeferredList.Num() > 0
		) {
			FScopeLock Lock(&engine->DeferredEventsCS);
			//TODO refactor with lambdas and subclass Reactional::FEventParams with common base struct
			{
				TArray<int32> EventNodesToRemove;
				TArray<int32> EventNodesToTrigger;
				TMap<int32, int32> EventNoteTriggerFrames;

				for (int32 notesDeferredIdx = 0; notesDeferredIdx < FReactionalEngine::GetEngine()->EventNotesDeferredList.Num(); notesDeferredIdx++)
				{
					Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->EventNotesDeferredList[notesDeferredIdx];
					if (noteParams.reactional_engine_beats_at_trigger <= currentBeat)
					{
						EventNodesToTrigger.AddUnique(notesDeferredIdx);
						EventNodesToRemove.AddUnique(notesDeferredIdx);
					}
				}
				if (EventNodesToTrigger.Num() > 0)
				{
					for (int32 notesToTriggerIdx = 0; notesToTriggerIdx < EventNodesToTrigger.Num(); notesToTriggerIdx++)
					{
						Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->EventNotesDeferredList[EventNodesToTrigger[notesToTriggerIdx]];
						if (noteParams.bParamsSourceNoteOn && noteParams.bParamsValid)
						{
							engine->ReactionalSubsystemWeakPtr->NoteOnEvent.Broadcast(noteParams.offset, noteParams.sink, noteParams.lane, noteParams.pitch, noteParams.velocity);
						}
						else if (noteParams.bParamsValid)
						{
							engine->ReactionalSubsystemWeakPtr->NoteOffEvent.Broadcast(noteParams.offset, noteParams.sink, noteParams.lane, noteParams.pitch, noteParams.velocity);
						}
					}
				}
				if (EventNodesToRemove.Num() > 0)
				{
					for (int32 notesToRemoveIdx = EventNodesToRemove.Num()-1; notesToRemoveIdx >= 0; notesToRemoveIdx--)
					{
						FReactionalEngine::GetEngine()->EventNotesDeferredList.RemoveAt(EventNodesToRemove[notesToRemoveIdx]);
					}
				}
			}

			{
				TArray<int32> EventNodesToRemove;
				TArray<int32> EventNodesToTrigger;
				TMap<int32, int32> EventBarBeatTriggerFrames;

				for (int32 DeferredIdx = 0; DeferredIdx < FReactionalEngine::GetEngine()->EventBarBeatDeferredList.Num(); DeferredIdx++)
				{
					Reactional::FEventBarBeatParams Params = FReactionalEngine::GetEngine()->EventBarBeatDeferredList[DeferredIdx];
					if (Params.reactional_engine_beats_at_trigger <= currentBeat)
					{
						EventNodesToTrigger.AddUnique(DeferredIdx);
						EventNodesToRemove.AddUnique(DeferredIdx);
					}
				}
				if (EventNodesToTrigger.Num() > 0)
				{
					for (int32 TriggerIdx = 0; TriggerIdx < EventNodesToTrigger.Num(); TriggerIdx++)
					{
						Reactional::FEventBarBeatParams Params = FReactionalEngine::GetEngine()->EventBarBeatDeferredList[EventNodesToTrigger[TriggerIdx]];
						if (Params.bParamsValid)
						{
							engine->ReactionalSubsystemWeakPtr->BarBeatEvent.Broadcast(Params.offset, Params.bar, Params.beat);
						}
					}
				}
				if (EventNodesToRemove.Num() > 0)
				{
					for (int32 RemoveIdx = EventNodesToRemove.Num() - 1; RemoveIdx >= 0; RemoveIdx--)
					{
						FReactionalEngine::GetEngine()->EventBarBeatDeferredList.RemoveAt(EventNodesToRemove[RemoveIdx]);
					}
				}
			}

			//{
			//	TArray<int32> EventNodesToRemove;
			//	TArray<int32> EventNodesToTrigger;
			//	TMap<int32, int32> EventStingerTriggerFrames;

			//	for (int32 DeferredIdx = 0; DeferredIdx < engine->EventStingerDeferredList.Num(); DeferredIdx++)
			//	{
			//		Reactional::FEventStingerParams Params = engine->EventStingerDeferredList[DeferredIdx];
			//		if (Params.reactional_engine_beats_at_trigger <= currentBeat)
			//		{
			//			EventNodesToTrigger.AddUnique(DeferredIdx);
			//			EventNodesToRemove.AddUnique(DeferredIdx);
			//		}
			//	}
			//	if (EventNodesToTrigger.Num() > 0)
			//	{
			//		for (int32 TriggerIdx = 0; TriggerIdx < EventNodesToTrigger.Num(); TriggerIdx++)
			//		{
			//			Reactional::FEventStingerParams Params = engine->EventStingerDeferredList[EventNodesToTrigger[TriggerIdx]];
			//			if (Params.bParamsValid)
			//			{
			//				engine->ReactionalSubsystemWeakPtr->StingerEvent.Broadcast(Params.offset, Params.startevent, Params.stingerorigin);
			//			}
			//		}
			//	}
			//	if (EventNodesToRemove.Num() > 0)
			//	{
			//		for (int32 RemoveIdx = EventNodesToRemove.Num() - 1; RemoveIdx >= 0; RemoveIdx--)
			//		{
			//			engine->EventStingerDeferredList.RemoveAt(EventNodesToRemove[RemoveIdx]);
			//		}
			//	}
			//}
		}

		if (engine->EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::MetasoundRender_DedicatedThreadEventProcessing
		 || engine->EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::MetasoundRender_GameThreadEventProcessing)
		{
			//remove all that are older than 0.25 beats
			if (engine->MetasoundEventsTriggerCS.TryLock())
			{
				for (int32 notesToRemoveIdx = engine->MetasoundEventNotesDeferredList.Num() - 1; notesToRemoveIdx >= 0; notesToRemoveIdx--)
				{
					Reactional::FEventNoteParams noteParams = engine->MetasoundEventNotesDeferredList[notesToRemoveIdx];
					if (noteParams.reactional_engine_beats_at_trigger <= currentBeat - 0.25)
					{
						engine->MetasoundEventNotesDeferredList.RemoveAt(notesToRemoveIdx);
					}
				}
				if (engine->MetasoundEventNotesDeferredList.Num() == 1)
				{
					//clear all then readd 1
					Reactional::FEventNoteParams noteParams = FReactionalEngine::GetEngine()->MetasoundEventNotesDeferredList[0];
					engine->MetasoundEventNoteIndexInArrayMap.Empty();
					engine->MetaSoundEventNoteOffsetValues.Empty();
					engine->MetaSoundEventNoteSinkValues.Empty();
					engine->MetaSoundEventNoteLaneValues.Empty();
					engine->MetaSoundEventNotePitchValues.Empty();
					engine->MetaSoundEventNoteVelocityValues.Empty();

					//safe to clear as we don't have two notes
					engine->MetaSoundEventNoteSharedTempFloatValues.Empty();
					engine->MetaSoundEventNoteSharedTempIntValues.Empty();

					engine->MetasoundEventNoteIndexInArrayMap.Add(noteParams.NoteEventGuid, 0);
					engine->MetaSoundEventNoteOffsetValues.Add(noteParams.offset);
					engine->MetaSoundEventNoteSinkValues.Add(noteParams.sink);
					engine->MetaSoundEventNoteLaneValues.Add(noteParams.lane);
					engine->MetaSoundEventNotePitchValues.Add(noteParams.pitch);
					engine->MetaSoundEventNoteVelocityValues.Add(noteParams.velocity);
				}
				else if (engine->MetasoundEventNotesDeferredList.Num() == 0)
				{
					//clear all
					engine->MetasoundEventNoteIndexInArrayMap.Empty();
					engine->MetaSoundEventNoteOffsetValues.Empty();
					engine->MetaSoundEventNoteSinkValues.Empty();
					engine->MetaSoundEventNoteLaneValues.Empty();
					engine->MetaSoundEventNotePitchValues.Empty();
					engine->MetaSoundEventNoteVelocityValues.Empty();
					engine->MetaSoundEventNoteSharedTempFloatValues.Empty();
					engine->MetaSoundEventNoteSharedTempIntValues.Empty();
				}
				engine->MetasoundEventsTriggerCS.Unlock();
			}
		}
	}
}

void UReactionalSynthComponent::OnBeginGenerate()
{
	ensure(FReactionalEngine::GetEngine());

	Super::OnBeginGenerate();
	//REACTIONAL_LOG_WARNING()
}

void UReactionalSynthComponent::OnEndGenerate()
{
	Super::OnEndGenerate();
	//REACTIONAL_LOG_WARNING()
}

int32 UReactionalSynthComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples)
{
	REACTIONAL_GET_LIB_PTR_OR_RETURN(0)

	int32 SampleRate = sampleRateFromInit;
	int32 frames = NumSamples / 2;
	{
		if (engine->EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::SynthComponentRender_DedicatedThreadEventProcessing
		 || engine->EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::SynthComponentRender_GameThreadEventProcessing
		) {
			int32 errorcode = reactional_render_interleaved(lib_ptr, SampleRate, frames, 2, OutAudio);
		}
	}
	return NumSamples;
}