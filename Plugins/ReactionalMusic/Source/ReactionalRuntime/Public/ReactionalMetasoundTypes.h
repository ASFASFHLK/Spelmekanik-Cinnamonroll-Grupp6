/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "Containers/Array.h"
#include "Containers/ArrayView.h"
#include "MetasoundDataReference.h"
#include "MetasoundDataTypeRegistrationMacro.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundPrimitives.h"

#define LOCTEXT_NAMESPACE "ReactionalMetasound"

namespace Reactional
{
	struct FMetasoundTestParams
	{
		FMetasoundTestParams() {}
		FMetasoundTestParams(float InOffset, int InSink, bool bInParamsSourceNoteOn) :
			offset(InOffset), sink(InSink), bParamsSourceNoteOn(bInParamsSourceNoteOn) {}

		float offset{ 0.0f };
		int sink{ 0 };

		bool bParamsSourceNoteOn = false;
	};
}

namespace Metasound
{
	namespace ReactionalVertexNames
	{
		METASOUND_PARAM(OutputTriggerOnNoteOn, "OnNoteOn", "Triggers when OnNoteOn is triggered.")
		METASOUND_PARAM(OutputTriggerOnNoteOff, "OnNoteOff", "Triggers when OnNoteOff is triggered.")
	}

	using FMetasoundTestParamsReadRef = TDataReadReference<Reactional::FMetasoundTestParams>;
	using FMetasoundTestParamsWriteRef = TDataWriteReference<Reactional::FMetasoundTestParams>;
	
	DECLARE_METASOUND_DATA_REFERENCE_TYPES(Reactional::FMetasoundTestParams, REACTIONALRUNTIME_API, FMetasoundTestParamsTypeInfo, FMetasoundTestParamsReadRef, FMetasoundTestParamsWriteRef)
}