/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalEditorStyle.h"
#include "ReactionalEditorStyle.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "EditorStyleSet.h"

TSharedPtr<FSlateStyleSet> FReactionalEditorStyle::StyleInstance = nullptr;

void FReactionalEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = MakeShareable(new FSlateStyleSet("ReactionalEditorStyle"));
		StyleInstance->SetContentRoot(FPaths::ProjectPluginsDir() / TEXT("ReactionalMusic/Resources"));

		// Define a 40x40 icon
		const FVector2D Icon40x40(40.0f, 40.0f);
		StyleInstance->Set("ReactionalWidget.Icon", new FSlateImageBrush(StyleInstance->RootToContentDir(TEXT("ReactionalIcon.png")), Icon40x40));

		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FReactionalEditorStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		ensure(StyleInstance.IsUnique());
		StyleInstance.Reset();
	}
}

FName FReactionalEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ReactionalEditorStyle"));
	return StyleSetName;
}

TSharedPtr<ISlateStyle> FReactionalEditorStyle::Get()
{
	return StyleInstance;
}