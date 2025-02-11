/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "DSP/FloatArrayMath.h"
#include "Internationalization/Text.h"
#include "MetasoundExecutableOperator.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundNodeRegistrationMacro.h"
#include "MetasoundAudioBuffer.h"
#include "MetasoundStandardNodesCategories.h"
#include "MetasoundExecutableOperator.h"     // TExecutableOperator class
#include "MetasoundPrimitives.h"             // ReadRef and WriteRef descriptions for bool, int32, float, and string
#include "MetasoundNodeRegistrationMacro.h"  // METASOUND_LOCTEXT and METASOUND_REGISTER_NODE macros
#include "MetasoundStandardNodesNames.h"     // StandardNodes namespace
#include "MetasoundFacade.h"				 // FNodeFacade class, eliminates the need for a fair amount of boilerplate code
#include "MetasoundParamHelper.h"            // METASOUND_PARAM and METASOUND_GET_PARAM family of macros
#include "MetasoundOperatorSettings.h"
#include "MetasoundDataTypeRegistrationMacro.h"
#include "ReactionalBPLibrary.h"
#include "ReactionalSubsystem.h"

#define LOCTEXT_NAMESPACE "ReactionalMetasound"

namespace Metasound
{
	namespace ReactionalNodes
	{
		const FName Namespace = "Reactional";
		const FName AudioVariant = "Audio";
	}

	namespace ReactionalNodesPrivate {}

	namespace ReactionalVertexNames
	{
		METASOUND_PARAM(LeftAudioOut, "Out Left Audio", "Left output synthesized audio.");
		METASOUND_PARAM(RightAudioOut, "Out Right Audio", "Right output synthesized audio.");
	}

	// Operator Class
	class FReactionalRenderAudioOperator : public TExecutableOperator<FReactionalRenderAudioOperator>
	{
	public:

		FReactionalRenderAudioOperator(const FOperatorSettings& InSettings)
			: LeftAudioOut(FAudioBufferWriteRef::CreateNew(InSettings))
			, RightAudioOut(FAudioBufferWriteRef::CreateNew(InSettings))
			, OperatorSettings(InSettings)
		{}

		static const FNodeClassMetadata& GetNodeInfo()
		{
			auto CreateNodeClassMetadata = []() -> FNodeClassMetadata
				{
					FVertexInterface NodeInterface = DeclareVertexInterface();

					FNodeClassMetadata Metadata
					{
						FNodeClassName { ReactionalNodes::Namespace, "ReactionalStereoTest", ReactionalNodes::AudioVariant },
						1, // Major Version
						0, // Minor Version
						METASOUND_LOCTEXT("ReactionalRenderAudioStereoDisplayName", "Reactional Music | RenderAudioStereo"),
						METASOUND_LOCTEXT("ReactionalRenderAudioStereoDesc", "Rendered audio stereo buffer from the reactional engine."),
						PluginAuthor,
						PluginNodeMissingPrompt,
						NodeInterface,
						{ NodeCategories::Music},
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
				),
				FOutputVertexInterface(
					TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(LeftAudioOut)),
					TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(RightAudioOut))
				)
			);

			return Interface;
		}

		virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override
		{
			//using namespace ReactionalVertexNames;
		
			//InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputAudioCarrier), AudioInputCarrier);
		}

		virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override
		{
			using namespace ReactionalVertexNames;

			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(LeftAudioOut), LeftAudioOut);
			InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(RightAudioOut), RightAudioOut);
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
			
			if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false)
			 && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr->EngineRenderAudioMode == EReactionalRenderMode::ReactionalRenderAudioMetaSounds
			) {
				TSharedRef<FReactionalEngine> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

				bReactionalMetaSoundsValid = true;
				currentBeatInstantiation = UReactionalBPLibrary::GetCurrentBeatAsDouble();
				currentBeatFirstRender = -1.0f;
			}
			else
			{
				bReactionalMetaSoundsValid = false;
			}
			return MakeUnique<FReactionalRenderAudioOperator>(InParams.OperatorSettings);
		}

		void Execute() const
		{
			double SampleRate = 48000.0;
			uint32 iSampleRate = 48000;
			uint32 iNumChannels = 2;

			float blockRate = OperatorSettings.GetTargetBlockRate();
			float actualblockRate = OperatorSettings.GetActualBlockRate();
			float sampleRate = OperatorSettings.GetSampleRate();

			int32 framesPerBlock = OperatorSettings.GetNumFramesPerBlock();

			static float tmp2048buffer[2048];
			FMemory::Memzero(tmp2048buffer, 2048 * sizeof(float));

			if ( bReactionalMetaSoundsValid )
			{
				TSharedRef<FReactionalEngine> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

				if ( currentBeatFirstRender < 0.0 )
				{
					if (FReactionalEngine::GetEngine() && FReactionalEngine::GetEngine()->ReactionalSubsystemWeakPtr.IsValid(false, false))
					{
						currentBeatFirstRender = UReactionalBPLibrary::GetCurrentBeatAsDouble();					
					}
				}

				void* lib_ptr = FReactionalEngine::GetEngine()->reactionallib_ptr();
				int rendererrorcode = reactional_render_interleaved(lib_ptr, (double)sampleRate, framesPerBlock, 2, tmp2048buffer);
				
				int32 leftIdx = 0;
				int32 rightIdx = 0;
				for (int idx = 0; idx < (framesPerBlock * 2); idx++)
				{
					if ((idx % 2) == 0)
					{
						float* ptr = LeftAudioOut->GetData() + leftIdx;
						*ptr = *(tmp2048buffer + idx);
						leftIdx++;
					}
					else if ((idx % 2) == 1)
					{
						float* ptr = RightAudioOut->GetData() + rightIdx;
						*ptr = *(tmp2048buffer + idx);
						rightIdx++;
					}
				}
			}
			else
			{
				int32 leftIdx = 0;
				int32 rightIdx = 0;
				for (int idx = 0; idx < (framesPerBlock * 2); idx++)
				{
					if ((idx % 2) == 0)
					{
						float* ptr = LeftAudioOut->GetData() + leftIdx;
						*ptr = 0.0f;
						leftIdx++;
					}
					else if ((idx % 2) == 1)
					{
						float* ptr = RightAudioOut->GetData() + rightIdx;
						*ptr = 0.0f;
						rightIdx++;
					}
				}
			}
		}

	private:

		// Audio output
		FAudioBufferWriteRef LeftAudioOut;
		FAudioBufferWriteRef RightAudioOut;

		const FOperatorSettings OperatorSettings;

		static bool bReactionalMetaSoundsValid;
		static double currentBeatInstantiation;
		static double currentBeatFirstRender;
	};

	// Node Class
	class FReactionalRenderAudioNode : public FNodeFacade
	{
	public:
		FReactionalRenderAudioNode(const FNodeInitData& InitData)
			: FNodeFacade(InitData.InstanceName, InitData.InstanceID, TFacadeOperatorClass<FReactionalRenderAudioOperator>()) {}
	};

	bool FReactionalRenderAudioOperator::bReactionalMetaSoundsValid = false;
	double FReactionalRenderAudioOperator::currentBeatInstantiation = std::numeric_limits<double>::max();
	double FReactionalRenderAudioOperator::currentBeatFirstRender = std::numeric_limits<double>::max();

	// Register node
	METASOUND_REGISTER_NODE(FReactionalRenderAudioNode)
}
#undef LOCTEXT_NAMESPACE