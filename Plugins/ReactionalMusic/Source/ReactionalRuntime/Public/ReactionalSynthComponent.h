/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/SynthComponent.h"
#include "Sound/SoundWave.h"
#include "ReactionalSynthComponent.generated.h"

UCLASS(ClassGroup=Synth, meta=(BlueprintSpawnableComponent))
class REACTIONALRUNTIME_API UReactionalSynthComponent : public USynthComponent
{
	GENERATED_BODY()

	UReactionalSynthComponent(const FObjectInitializer& ObjInitializer) : Super(ObjInitializer)
	{
		PrimaryComponentTick.bCanEverTick = true;
	}

	// Initialize the synth component
	virtual bool Init(int32& SampleRate) override;
	virtual bool IsReadyForFinishDestroy() override;

	// Called to generate more audio
	virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;
	virtual void OnBeginGenerate() override;
	virtual void OnEndGenerate() override;

	//~ Begin ActorComponent Interface.
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//~ End ActorComponent Interface

public:
	int32 GetNumChannels() const { return NumChannels; }
	int32 sampleRateFromInit = -1;
};
