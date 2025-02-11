/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalEngine.h"
#include "ReactionalBPLibrary.h"
#include "ReactionalSubsystem.h"

#define LOCTEXT_NAMESPACE "ReactionalMusic"

#pragma optimize("", off)

int32 Reactional::FOSCMessage::Decode(const void* OscData, int32 OscSize, int maxValues)
{
	int32 outReturn_Result;
	int32 numValues = 0;

	const char* decoded_out_address = nullptr;
	int32 decoded_out_address_size = 0;
	const char* decoded_out_typetag = nullptr;
	int32 decoded_out_typetag_size = 0;
	int32 inparam_max_values = maxValues;
	int32 decoded_out_numvalues = 0;

	TArray<uint8> valuesbyteBuffer;
	valuesbyteBuffer.AddZeroed(sizeof(reactional_osc_value) * maxValues);
	void* decoded_out_voidptr = static_cast<void*>(valuesbyteBuffer.GetData());
	reactional_osc_value* decoded_out_oscvaluesptr = static_cast<reactional_osc_value*>(decoded_out_voidptr);

	outReturn_Result = reactional_osc_message_decode(
		OscData,
		OscSize,
		&decoded_out_address,
		&decoded_out_address_size,
		&decoded_out_typetag,
		&decoded_out_typetag_size,
		inparam_max_values,
		decoded_out_oscvaluesptr,
		&decoded_out_numvalues
	);

	this->Address = FString(ANSI_TO_TCHAR(decoded_out_address));
	this->TypeTag = FString(ANSI_TO_TCHAR(decoded_out_typetag));
	this->Values.AddDefaulted(decoded_out_numvalues);

	for (int valueIdx = 0; valueIdx < this->Values.Num(); valueIdx++)
	{
		TCHAR CurrentChar = this->TypeTag.GetCharArray()[valueIdx];
		if (CurrentChar == TEXT('i'))
		{
			this->Values[valueIdx].i = (decoded_out_oscvaluesptr + valueIdx)->i;
		}
		else if (CurrentChar == TEXT('f'))
		{
			this->Values[valueIdx].f = (decoded_out_oscvaluesptr + valueIdx)->f;
		}
		else if (CurrentChar == TEXT('s'))
		{
			this->Values[valueIdx].i = (decoded_out_oscvaluesptr + valueIdx)->i;
		}
		else if (CurrentChar == TEXT('b'))
		{
			this->Values[valueIdx].i = (decoded_out_oscvaluesptr + valueIdx)->i;
		}
		else if (CurrentChar == TEXT('h'))
		{
			this->Values[valueIdx].h = (decoded_out_oscvaluesptr + valueIdx)->h;
		}
		else if (CurrentChar == TEXT('t'))
		{
			this->Values[valueIdx].t = (decoded_out_oscvaluesptr + valueIdx)->t;
		}
		else if (CurrentChar == TEXT('d'))
		{
			this->Values[valueIdx].i = (decoded_out_oscvaluesptr + valueIdx)->d;
		}
		else if (CurrentChar == TEXT('S'))
		{
			this->Values[valueIdx].i = (decoded_out_oscvaluesptr + valueIdx)->i;
		}
		else if (CurrentChar == TEXT('c'))
		{
			this->Values[valueIdx].c = (decoded_out_oscvaluesptr + valueIdx)->c;
		}
		else if (CurrentChar == TEXT('r'))
		{
			this->Values[valueIdx].r = (decoded_out_oscvaluesptr + valueIdx)->r;
		}
		else if (CurrentChar == TEXT('m'))
		{
			this->Values[valueIdx].i = (decoded_out_oscvaluesptr + valueIdx)->i;
		}
		else if (CurrentChar == TEXT('T'))
		{
			this->Values[valueIdx].TF = true;
		}
		else if (CurrentChar == TEXT('F'))
		{
			this->Values[valueIdx].TF = false;
		}
		else if (CurrentChar == TEXT('N'))
		{
			//Add null?
		}
		else if (CurrentChar == TEXT('I'))
		{
			//Do nothing
		}
		else
		{
			return -1;
		}

		this->Values[valueIdx].TypeTagCode.Empty(0);
		this->Values[valueIdx].TypeTagCode.InsertAt(0, CurrentChar);
	}

	return outReturn_Result;
}

int32 Reactional::FOSCMessage::FindInvalidValue(const TArray<Reactional::FOSCValue>& ValuesToCheck)
{
	for (int i = 0; i < ValuesToCheck.Num(); i++)
	{
		if (ValuesToCheck[i].TypeTagCode.Equals(TEXT("?")))
		{
			return i;
		}
	}
	return -1;
}

FReactionalProcessCallTaskRunnable::FReactionalProcessCallTaskRunnable()
{
	Thread = TUniquePtr<FRunnableThread>(FRunnableThread::Create(this, TEXT("FReactionalProcessCallTaskRunnable"), 0, TPri_Normal));
}

void FReactionalProcessCallTaskRunnable::EnsureCompletion() const
{
	if (Thread.IsValid())
	{
		Thread->WaitForCompletion();
	}
}

void FReactionalProcessCallTaskRunnable::Exit()
{
	if (FReactionalEngine::GetEngine())
	{
		FScopeLock Lock(&FReactionalEngine::GetEngine()->DedicatedThreadProcessCS);
	}
	REACTIONAL_LOG("Exit")
}

// gin:
//	here temporarily until reimpl of synth component
void TriggerMetaSoundEvents()
{
#ifdef WITH_EDITOR
	if(GEngine->GetWorld() != nullptr && GEngine->GetWorld()->WorldType == EWorldType::Game) { return; }
#endif
	
	AsyncTask(ENamedThreads::Type::GameThread, [] {
		//REACTIONAL_LOG("running")
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
		
					for (int32 notesDeferredIdx = 0; notesDeferredIdx < engine->EventNotesDeferredList.Num(); notesDeferredIdx++)
					{
						Reactional::FEventNoteParams noteParams = engine->EventNotesDeferredList[notesDeferredIdx];
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
							Reactional::FEventNoteParams noteParams = engine->EventNotesDeferredList[EventNodesToTrigger[notesToTriggerIdx]];
							if (noteParams.bParamsSourceNoteOn && noteParams.bParamsValid)
							{
								engine->ReactionalSubsystemWeakPtr->NoteOnEvent.Broadcast(
									noteParams.offset,
									noteParams.sink,
									noteParams.lane,
									noteParams.pitch,
									noteParams.velocity
								);
							}
							else if (noteParams.bParamsValid)
							{
								engine->ReactionalSubsystemWeakPtr->NoteOffEvent.Broadcast(
									noteParams.offset,
									noteParams.sink, 
									noteParams.lane,
									noteParams.pitch,
									noteParams.velocity
								);
							}
						}
					}
					if (EventNodesToRemove.Num() > 0)
					{
						for (int32 notesToRemoveIdx = EventNodesToRemove.Num()-1; notesToRemoveIdx >= 0; notesToRemoveIdx--)
						{
							engine->EventNotesDeferredList.RemoveAt(EventNodesToRemove[notesToRemoveIdx]);
						}
					}
				}
		
				{
					TArray<int32> EventNodesToRemove;
					TArray<int32> EventNodesToTrigger;
					TMap<int32, int32> EventBarBeatTriggerFrames;
		
					for (int32 DeferredIdx = 0; DeferredIdx < engine->EventBarBeatDeferredList.Num(); DeferredIdx++)
					{
						Reactional::FEventBarBeatParams Params = engine->EventBarBeatDeferredList[DeferredIdx];
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
							Reactional::FEventBarBeatParams Params = engine->EventBarBeatDeferredList[EventNodesToTrigger[TriggerIdx]];
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
							engine->EventBarBeatDeferredList.RemoveAt(EventNodesToRemove[RemoveIdx]);
						}
					}
				}
		
				//{
			//		TArray<int32> EventNodesToRemove;
			//		TArray<int32> EventNodesToTrigger;
			//		TMap<int32, int32> EventStingerTriggerFrames;
		
			//		for (int32 DeferredIdx = 0; DeferredIdx < engine->EventStingerDeferredList.Num(); DeferredIdx++)
			//		{
			//			Reactional::FEventStingerParams Params = engine->EventStingerDeferredList[DeferredIdx];
			//			if (Params.reactional_engine_beats_at_trigger <= currentBeat)
			//			{
			//				EventNodesToTrigger.AddUnique(DeferredIdx);
			//				EventNodesToRemove.AddUnique(DeferredIdx);
			//			}
			//		}
			//		if (EventNodesToTrigger.Num() > 0)
			//		{
			//			for (int32 TriggerIdx = 0; TriggerIdx < EventNodesToTrigger.Num(); TriggerIdx++)
			//			{
			//				Reactional::FEventStingerParams Params = engine->EventStingerDeferredList[EventNodesToTrigger[TriggerIdx]];
			//				if (Params.bParamsValid)
			//				{
			//					engine->ReactionalSubsystemWeakPtr->StingerEvent.Broadcast(
			//						Params.offset,
			//						Params.startevent,
			//						Params.stingerorigin
			//					);
			//				}
			//			}
			//		}
			//		if (EventNodesToRemove.Num() > 0)
			//		{
			//			for (int32 RemoveIdx = EventNodesToRemove.Num() - 1; RemoveIdx >= 0; RemoveIdx--)
			//			{
			//				engine->EventStingerDeferredList.RemoveAt(EventNodesToRemove[RemoveIdx]);
			//			}
			//		}
			//	}
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
						Reactional::FEventNoteParams noteParams = engine->MetasoundEventNotesDeferredList[0];
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
	});
}

uint32 FReactionalProcessCallTaskRunnable::Run()
{
	while (!bShouldExit)
	{
		if (bShouldRun)
		{
			if (FReactionalEngine::GetEngine())
			{
				FScopeLock Lock(&FReactionalEngine::GetEngine()->DedicatedThreadProcessCS);
				// markus:
				//	This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation.
				TSharedRef<FReactionalEngine, ESPMode::ThreadSafe> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();
				int ErrorCode = reactional_process(SharedEngineRef->reactionallib_ptr(), -1);
				SharedEngineRef->GetEvents(-1);
				TriggerMetaSoundEvents();
			}
			if (!bShouldExit)
			{
				FPlatformProcess::Sleep(0.016f);
			}
		}
		else if (!bShouldExit) // bShouldRun false, yield thread
		{
			FPlatformProcess::Sleep(0.0f);
		}
	}

	REACTIONAL_LOG("Stopping engine event processing.")
	return 0;
}

TSharedPtr<FReactionalEngine, ESPMode::ThreadSafe> FReactionalEngine::MakeSharedInstance()
{
	if (InstanceWeakPtr.IsValid()) { return InstanceWeakPtr.Pin(); }

	TSharedPtr<FReactionalEngine, ESPMode::ThreadSafe> engineInst = MakeShareable(new FReactionalEngine);
	InstanceWeakPtr = engineInst;

	// markus:
	//	TODO look into RAII for constructor
	engineInst->ReactionalUniquePtr = MakeUnique<FReactionalLibPtr>(reactional_new());
	REACTIONAL_LOG("New UniquePtr created.")

	return engineInst;
}

bool FReactionalEngine::ThreadingRenderingStateIsDedicatedRunning() const
{
	return (EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::SynthComponentRender_DedicatedThreadEventProcessing
		||	EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::MetasoundRender_DedicatedThreadEventProcessing);
}

bool FReactionalEngine::ThreadingRenderingStateIsGameThreadRunning() const
{
	return (EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::SynthComponentRender_GameThreadEventProcessing
		||	EngineThreadingRenderingState == EReactionalEngineThreadingRenderingState::MetasoundRender_GameThreadEventProcessing);
}

void FReactionalEngine::CreateDedicatedThread()
{
	if (!ReactionalProcessCallTask.IsValid())
	{
		ReactionalProcessCallTask = MakeUnique<FReactionalProcessCallTaskRunnable>();
	}
}

void FReactionalEngine::StopDedicatedThread() const
{
	if (ReactionalProcessCallTask.IsValid())
	{
		ReactionalProcessCallTask->bShouldRun = false;
		ReactionalProcessCallTask->bShouldExit = true;
	}
}

void FReactionalEngine::BindStaticDelegates()
{
	NoteOnEventStaticDelegate.BindRaw(this, &FReactionalEngine::Event_NoteOn_Dispatch);
	NoteOffEventStaticDelegate.BindRaw(this, &FReactionalEngine::Event_NoteOff_Dispatch);
	//StingerEventStaticDelegate.BindRaw(this, &FReactionalEngine::Event_Stinger_Dispatch);
	AudioEndEventStaticDelegate.BindRaw(this, &FReactionalEngine::Event_AudioEnd_Dispatch);
	BarBeatEventStaticDelegate.BindRaw(this, &FReactionalEngine::Event_BarBeatEvent_Dispatch);
	PartEventStaticDelegate.BindRaw(this, &FReactionalEngine::Event_PartEvent_Dispatch);
}

void FReactionalEngine::GetEvents(int trackid)
{
	OSCEventMessages.Empty();

	int64_t startBeat = 0;
	EventPoll(trackid, startBeat, OSCEventMessages);

	for (int32 OSCMsgIdx = 0; OSCMsgIdx < OSCEventMessages.Num(); OSCMsgIdx++)
	{
		Reactional::FOSCMessage OSCMsg = OSCEventMessages[OSCMsgIdx];
		//REACTIONAL_LOG("OSC Msg: %s", *OSCMsg.Address)
		if (OSCMsg.Address.Equals(TEXT("/noteon")))
		{
			// h i i f f
			NoteOnEventStaticDelegate.ExecuteIfBound(
				OSCMsg.Values[0].h / 1'000'000.0,
				OSCMsg.Values[1].i,
				OSCMsg.Values[2].i,
				OSCMsg.Values[3].f,
				OSCMsg.Values[4].f
			);
		}
		else if (OSCMsg.Address.Equals(TEXT("/noteof")))
		{
			// h i i f f
			NoteOffEventStaticDelegate.ExecuteIfBound(
				OSCMsg.Values[0].h / 1'000'000.0,
				OSCMsg.Values[1].i,
				OSCMsg.Values[2].i,
				OSCMsg.Values[3].f,
				OSCMsg.Values[4].f
			);
		}
		//else if (OSCMsg.Address.Equals(TEXT("/stinger/start")))
		//{	// h _ 3)
		//	StingerEventStaticDelegate.ExecuteIfBound(
		//		OSCMsg.Values[0].h / 1'000'000.0,
		//		true,
		//		OSCMsg.Values[3].i
		//	);
		//}
		//else if (OSCMsg.Address.Equals(TEXT("/stinger/stop")))
		//{
		//	// h _ 3)
		//	StingerEventStaticDelegate.ExecuteIfBound(
		//		OSCMsg.Values[0].h / 1'000'000.0,
		//		false,
		//		OSCMsg.Values[3].i
		//	);
		//}
		else if (OSCMsg.Address.Equals(TEXT("/audio/end")))
		{
			AudioEndEventStaticDelegate.ExecuteIfBound();
		}
		else if (OSCMsg.Address.Equals(TEXT("/bar")))
		{	// h i i (gin: should maybe be 'h i i i i')
			BarBeatEventStaticDelegate.ExecuteIfBound(
				OSCMsg.Values[0].h / 1'000'000.0,
				OSCMsg.Values[3].i,
				OSCMsg.Values[4].i
			);
		}
		else if (OSCMsg.Address.Equals(TEXT("/part")))
		{	// i (gin: should maybe be 'h i i i')
			PartEventStaticDelegate.ExecuteIfBound();
		}
	}
	OSCEventMessages.Empty();

	if(!ReactionalSubsystemWeakPtr.IsValid()) { return; }
	int64 Microbeat = UReactionalPlaybackLibrary::MusicSystem_GetCurrentMicroBeat();
	for(int i = 0; i < static_cast<int>(EReactionalQuantizationValue::Count); i++)
	{
		UReactionalSubsystem::FReactionalDelegateData& event = ReactionalSubsystemWeakPtr->QuantizationEvents[i];
		FReactionalQuantizationEventMCDelegate& delegate = event.Delegate;
		int64& last_quant = event.LastQuant;
		if(delegate.IsBound())
		{
			double Quant = QuantToDouble(static_cast<EReactionalQuantizationValue>(i)) * 4'000'000;
			if(last_quant > Microbeat && Microbeat > 0) { last_quant = FMath::CeilToInt64(Microbeat / Quant) * Quant; }
			if(last_quant <= 0) { last_quant = FMath::CeilToInt64(Microbeat / Quant) * Quant; return; }
			if(Microbeat >= last_quant)
			{
				last_quant = FMath::CeilToInt64(Microbeat / Quant) * Quant;
				// needs to be called on game thread if we want to use timelines etc.
				AsyncTask(ENamedThreads::Type::GameThread, [=]{ delegate.Broadcast(); });
			}
		}
	}
}

void FReactionalEngine::EventPoll(int id, int64_t& startBeat, TArray<Reactional::FOSCMessage>& OutEventMessages, int maxMessages) const
{
	auto* lib_ptr = this->reactionallib_ptr();
	if(lib_ptr == nullptr) { return; }
	
	int32 num = reactional_event_poll_begin(lib_ptr, id, &startBeat);

	if (maxMessages > 0 && num > maxMessages)
	{
		num = maxMessages;
	}
	if (num > 0)
	{
		OutEventMessages.AddDefaulted(num);
		int32 messageCount = 0;
		for (int32 i = 0; i < num; i++)
		{
			int32 oscSize = 0;
			const void* oscDataPtr = reactional_event_poll(lib_ptr, id, i, &oscSize);
			if (oscSize > 0 && oscDataPtr != nullptr)
			{
				Reactional::FOSCMessage Msg;
				int32 result = Msg.Decode(oscDataPtr, oscSize);
				if (result < 0)
				{
					OutEventMessages.Empty();
					return;
				}
				OutEventMessages[messageCount++] = Msg;
			}
		}
		reactional_event_poll_end(lib_ptr, id, num);
		OutEventMessages.SetNum(messageCount);
	}
}

void FReactionalEngine::Event_NoteOn_Dispatch(double offset, int32 sink, int32 lane, float pitch, float velocity)
{
	auto* lib_ptr = this->reactionallib_ptr();
	if(lib_ptr == nullptr) { return; }
	
	if (GetSubsystem())
	{
		Reactional::FEventNoteParams DeferredEventNoteParams(offset, sink, lane, pitch, velocity, true, true);
		DeferredEventNoteParams.reactional_engine_beats_at_poll = UReactionalBPLibrary::GetCurrentBeatAsDouble();
		DeferredEventNoteParams.reactional_engine_frames_at_poll = reactional_get_frames_from_beats(lib_ptr, -1, DeferredEventNoteParams.reactional_engine_beats_at_poll);
		DeferredEventNoteParams.reactional_engine_time_at_poll = reactional_get_time_from_beats(lib_ptr, -1, DeferredEventNoteParams.reactional_engine_beats_at_poll);

		DeferredEventNoteParams.reactional_engine_beats_at_trigger = offset;
		DeferredEventNoteParams.reactional_engine_frames_at_trigger = reactional_get_frames_from_beats(lib_ptr, -1, offset);
		DeferredEventNoteParams.reactional_engine_time_at_trigger = reactional_get_time_from_beats(lib_ptr, -1, offset);

		DeferredEventNoteParams.NoteEventGuid = FGuid::NewGuid();

		{
			FScopeLock Lock(&DeferredEventsCS);
			EventNotesDeferredList.Insert(DeferredEventNoteParams, 0);
		}
		if (ReactionalSubsystemWeakPtr->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds)
		{
			FScopeLock Lock(&GetEngine()->MetasoundEventsTriggerCS);
			MetasoundEventNotesDeferredList.Insert(DeferredEventNoteParams, 0);
			MetasoundEventNoteIndexInArrayMap.Add(DeferredEventNoteParams.NoteEventGuid, MetaSoundEventNoteOffsetValues.Num());
			MetaSoundEventNoteOffsetValues.Add(offset);
			MetaSoundEventNoteSinkValues.Add(sink);
			MetaSoundEventNoteLaneValues.Add(lane);
			MetaSoundEventNotePitchValues.Add(pitch);
			MetaSoundEventNoteVelocityValues.Add(velocity);
		}
	}
}

void FReactionalEngine::Event_NoteOff_Dispatch(double offset, int32 sink, int32 lane, float pitch, float velocity)
{
	auto* lib_ptr = this->reactionallib_ptr();
	if(lib_ptr == nullptr) { return; }
	
	if (GetSubsystem())
	{
		Reactional::FEventNoteParams NoteParams(offset, sink, lane, pitch, velocity, false, true);
		NoteParams.reactional_engine_beats_at_poll = UReactionalBPLibrary::GetCurrentBeatAsDouble();
		NoteParams.reactional_engine_frames_at_poll = reactional_get_frames_from_beats(lib_ptr, -1, NoteParams.reactional_engine_beats_at_poll);
		NoteParams.reactional_engine_time_at_poll = reactional_get_time_from_beats(lib_ptr, -1, NoteParams.reactional_engine_beats_at_poll);

		NoteParams.reactional_engine_beats_at_trigger = offset;
		NoteParams.reactional_engine_frames_at_trigger = reactional_get_frames_from_beats(lib_ptr, -1, offset);
		NoteParams.reactional_engine_time_at_trigger = reactional_get_time_from_beats(lib_ptr, -1, offset);

		NoteParams.NoteEventGuid = FGuid::NewGuid();

		{
			FScopeLock Lock(&DeferredEventsCS);
			EventNotesDeferredList.Insert(NoteParams, 0);
		}
		if (ReactionalSubsystemWeakPtr->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds)
		{
			FScopeLock Lock(&GetEngine()->MetasoundEventsTriggerCS);
			MetasoundEventNotesDeferredList.Insert(NoteParams, 0);
			MetasoundEventNoteIndexInArrayMap.Add(NoteParams.NoteEventGuid, MetaSoundEventNoteOffsetValues.Num());
			MetaSoundEventNoteOffsetValues.Add(offset);
			MetaSoundEventNoteSinkValues.Add(sink);
			MetaSoundEventNoteLaneValues.Add(lane);
			MetaSoundEventNotePitchValues.Add(pitch);
			MetaSoundEventNoteVelocityValues.Add(velocity);
		}
	}
}

// markus:
//	Todo how does these relate timing wise to the deferred events above, should all be deferred?
void FReactionalEngine::Event_Stinger_Dispatch(double offset, bool startevent, int32 stingerOrigin)
{
	auto* lib_ptr = this->reactionallib_ptr();
	if(lib_ptr == nullptr) { return; }
	
	if (GetSubsystem())
	{
		Reactional::FEventStingerParams StingerParams(offset, startevent, stingerOrigin, true);
		StingerParams.reactional_engine_beats_at_poll = UReactionalBPLibrary::GetCurrentBeatAsDouble();
		StingerParams.reactional_engine_frames_at_poll = reactional_get_frames_from_beats(lib_ptr, -1, StingerParams.reactional_engine_beats_at_poll);
		StingerParams.reactional_engine_time_at_poll = reactional_get_time_from_beats(lib_ptr, -1, StingerParams.reactional_engine_beats_at_poll);

		StingerParams.reactional_engine_beats_at_trigger = offset;
		StingerParams.reactional_engine_frames_at_trigger = reactional_get_frames_from_beats(lib_ptr, -1, offset);
		StingerParams.reactional_engine_time_at_trigger = reactional_get_time_from_beats(lib_ptr, -1, offset);

		StingerParams.StingerEventGuid = FGuid::NewGuid();
		{
			FScopeLock Lock(&DeferredEventsCS);
			EventStingerDeferredList.Insert(StingerParams, 0);
		}
	}
}

void FReactionalEngine::Event_BarBeatEvent_Dispatch(double offset, int32 bar, int32 beat)
{
	auto* lib_ptr = this->reactionallib_ptr();
	if(lib_ptr == nullptr) { return; }
	
	if (GetSubsystem())
	{
		Reactional::FEventBarBeatParams BarBeatParams(offset, bar, beat, true);
		BarBeatParams.reactional_engine_beats_at_poll = UReactionalBPLibrary::GetCurrentBeatAsDouble();
		BarBeatParams.reactional_engine_frames_at_poll = reactional_get_frames_from_beats(lib_ptr, -1, BarBeatParams.reactional_engine_beats_at_poll);
		BarBeatParams.reactional_engine_time_at_poll = reactional_get_time_from_beats(lib_ptr, -1, BarBeatParams.reactional_engine_beats_at_poll);

		BarBeatParams.reactional_engine_beats_at_trigger = offset;
		BarBeatParams.reactional_engine_frames_at_trigger = reactional_get_frames_from_beats(lib_ptr, -1, offset);
		BarBeatParams.reactional_engine_time_at_trigger = reactional_get_time_from_beats(lib_ptr, -1, offset);

		BarBeatParams.BarBeatEventGuid = FGuid::NewGuid();
		{
			FScopeLock Lock(&DeferredEventsCS);
			EventBarBeatDeferredList.Insert(BarBeatParams, 0);
		}
	}
}

void FReactionalEngine::Event_PartEvent_Dispatch() const
{
	if (ReactionalSubsystemWeakPtr.IsValid())
	{
		ReactionalSubsystemWeakPtr->PartEvent.Broadcast();
	}
}

void FReactionalEngine::Event_AudioEnd_Dispatch() const
{
	if (ReactionalSubsystemWeakPtr.IsValid())
	{
		ReactionalSubsystemWeakPtr->AudioEndEvent.Broadcast();
	}
}

// markus:
//	These should return another buffer if there is more than one noteon event with same sink on the same frame.
TArrayView<float> FReactionalEngine::MetasoundGetEventNoteViewOffset(double currentBeat, const FGuid Guid, const int32 SinkFilter)
{
	int32 idx = MetasoundEventNoteIndexInArrayMap.FindChecked(Guid);

	TArrayView<float> TAVfl(MetaSoundEventNoteOffsetValues.GetData() + idx, 1);
	return TAVfl;
}

TArrayView<int32> FReactionalEngine::MetasoundGetEventNoteViewSink(double currentBeat, const FGuid Guid, const int32 SinkFilter)
{
	int32 idx = MetasoundEventNoteIndexInArrayMap.FindChecked(Guid);

	TArrayView<int32> TAVint(MetaSoundEventNoteSinkValues.GetData() + idx, 1);
	return TAVint;
}

TArrayView<int32> FReactionalEngine::MetasoundGetEventNoteViewLane(double currentBeat, const FGuid Guid, const int32 SinkFilter)
{
	int32 idx = MetasoundEventNoteIndexInArrayMap.FindChecked(Guid);

	TArrayView<int32> TAVint(MetaSoundEventNoteLaneValues.GetData() + idx, 1);
	return TAVint;
}

TArrayView<float> FReactionalEngine::MetasoundGetEventNoteViewPitch(double currentBeat, const FGuid Guid, const int32 SinkFilter)
{
	int32 idx = MetasoundEventNoteIndexInArrayMap.FindChecked(Guid);

	TArrayView<float> TAVfl(MetaSoundEventNotePitchValues.GetData() + idx, 1);
	return TAVfl;
}

TArrayView<float> FReactionalEngine::MetasoundGetEventNoteViewVelocity(double currentBeat, const FGuid Guid, const int32 SinkFilter)
{
	int32 idx = MetasoundEventNoteIndexInArrayMap.FindChecked(Guid);

	TArrayView<float> TAVfl(MetaSoundEventNoteVelocityValues.GetData() + idx, 1);
	return TAVfl;
}

FReactionalEngine::~FReactionalEngine()
{
	if (ReactionalProcessCallTask.IsValid())
	{
		StopDedicatedThread();
		ReactionalProcessCallTask->EnsureCompletion();
		ReactionalProcessCallTask = nullptr;
	}
	if (ReactionalUniquePtr.IsValid())
	{
		reactional_free(reactionallib_ptr());
		ReactionalUniquePtr = nullptr;
		REACTIONAL_LOG("Deinitialized engine and released UniquePtr.")
	}
}

TWeakPtr<FReactionalEngine> FReactionalEngine::InstanceWeakPtr = nullptr;

#pragma optimize("", on)
#undef LOCTEXT_NAMESPACE