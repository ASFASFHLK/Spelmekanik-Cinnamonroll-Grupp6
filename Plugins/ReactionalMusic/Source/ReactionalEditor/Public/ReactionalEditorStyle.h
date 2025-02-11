/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "Styling/SlateStyle.h"

class FReactionalEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static FName GetStyleSetName();

	static TSharedPtr<class ISlateStyle> Get();

private:
	static TSharedPtr<class FSlateStyleSet> StyleInstance;
};