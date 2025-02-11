/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalBundleDataAssetDetailsCustomization.h"

#include "AssetThumbnail.h"
#include "AssetToolsModule.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Editor.h"
#include "EditorDirectories.h"
#include "IAssetTools.h"
#include "DesktopPlatformModule.h"
#include "PropertyCustomizationHelpers.h"
#include "IDetailChildrenBuilder.h"
#include "ScopedTransaction.h"
#include "Misc/PackageName.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Dialogs/Dialogs.h"
#include "SKismetInspector.h"
#include "ReactionalEngine.h"

#define LOCTEXT_NAMESPACE "FReactionalEditorModule"
#pragma optimize("", off)
TSharedRef<IPropertyTypeCustomization> FReactionalBundlePropertyTypeCustomization::MakeInstance()
{
	return MakeShareable(new FReactionalBundlePropertyTypeCustomization);
}

void FReactionalBundlePropertyTypeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = InStructPropertyHandle;
	check(CastFieldChecked<FStructProperty>(StructPropertyHandle->GetProperty())->Struct == FReactionalBundle::StaticStruct());

	FolderPathHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FReactionalBundle, BundlePath));

	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			StructPropertyHandle->CreatePropertyValueWidget()
		];
}
/*
void FReactionalBundlePropertyTypeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = InStructPropertyHandle;

	if (StructPropertyHandle.IsValid())
	{
		//FName FilterStructName;
		//const bool bAllowClear = !(StructPropertyHandle->GetMetaDataProperty()->PropertyFlags & CPF_NoClear);

		//if (StructPropertyHandle->HasMetaData(FDataRegistryType::ItemStructMetaData))
		//{
		//	const FString& RowType = StructPropertyHandle->GetMetaData(FDataRegistryType::ItemStructMetaData);
		//	FilterStructName = FName(*RowType);
		//}

		HeaderRow
			.NameContent()
			[
				StructPropertyHandle->CreatePropertyNameWidget()
			]
			.ValueContent()
			.MinDesiredWidth(250.0f)
			.MaxDesiredWidth(0.0f)
			[
				//PropertyCustomizationHelpers::MakePropertyComboBox(InStructPropertyHandle, FOnGetPropertyComboBoxStrings::CreateStatic(&FDataRegistryEditorModule::GenerateDataRegistryTypeComboBoxStrings, bAllowClear, FilterStructName))
			
				PropertyCustomizationHelpers::MakePropertyComboBox(
					StructPropertyHandle,
					FOnGetPropertyComboBoxStrings::CreateLambda([](TArray<TSharedPtr<FString>>& OutComboBoxStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) -> void
						{
							OutComboBoxStrings.Add(MakeShared<FString>(TEXT("WASSA")));
							OutRestrictedItems.Add(false);
							OutToolTips.Add(SNew(SToolTip).Text(LOCTEXT("WASSA2", "WASSA 2")));

							//for (const FAudioQualitySettings& i : GetDefault<UAudioSettings>()->QualityLevels)
							//{
							//	OutComboBoxStrings.Add(MakeShared<FString>(i.DisplayName.ToString()));
							//	OutRestrictedItems.Add(false);
							//	OutToolTips.Add(SNew(SToolTip).Text(i.DisplayName));
							//}
						}),
					FOnGetPropertyComboBoxValue::CreateLambda([]() -> FString
						{
							//int32 IndexVal = INDEX_NONE;
							//StructPropertyHandle->GetValue(IndexVal);
							//return GetDefault<UAudioSettings>()->FindQualityNameByIndex(IndexVal);
							return FString(TEXT("VALUE"));
						}),
					FOnPropertyComboBoxValueSelected::CreateLambda([](FString Value) -> void
						{
							//const TArray<FAudioQualitySettings>& Values = GetDefault<UAudioSettings>()->QualityLevels;
							//int32 Index = Values.IndexOfByPredicate([TextValue = FText::FromString(Value)](const FAudioQualitySettings& i) -> bool { return i.DisplayName.CompareTo(TextValue) == 0; });
							//StructPropertyHandle->SetValue(Index);
						})
				)
			
			];
	}
}
*/
/*
void FReactionalBundlePropertyTypeCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	uint32 NumChildren = 0;
	StructPropertyHandle->GetNumChildren(NumChildren);

	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{

	}
}
*/
void FReactionalBundlePropertyTypeCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	if (InStructPropertyHandle->IsValidHandle())
	{
		uint32 NumChildren = 0;
		InStructPropertyHandle->GetNumChildren(NumChildren);

		for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ChildIndex++)
		{
			ChildBuilder.AddProperty(InStructPropertyHandle->GetChildHandle(ChildIndex).ToSharedRef());
		}
	}
	ChildBuilder.AddCustomRow(LOCTEXT("ReactionalBundle", "ReactionalBundle"))
		.NameContent()
		[
			SNew(STextBlock)
				.Text(FText::FromString(TEXT("")))
				.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		[
			SNew(SButton)
				.OnClicked(this, &FReactionalBundlePropertyTypeCustomization::OnBrowsePathClicked)
				.ContentPadding(FMargin(2))
				.Content()
				[
					SNew(STextBlock)
						.Justification(ETextJustify::Left)
						.Text(LOCTEXT("BrowsePath", "Set Manifest Path..."))
				]
		];
}

TSharedRef<IDetailCustomization> FReactionalBundleDetailCustomization::MakeInstance()
{
	return MakeShareable(new FReactionalBundleDetailCustomization());
}

void FReactionalBundleDetailCustomization::CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder)
{
	DetailBuilderWeakPtr = DetailBuilder;
	CustomizeDetails(*DetailBuilder);
}

void FReactionalBundleDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{

}

FReply FReactionalBundlePropertyTypeCustomization::OnBrowsePathClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	const FText Title = LOCTEXT("Browse...", "Browse...");
	FString FileTypes = "manifest.json|*.json";

	static const FString ManifestFilename = TEXT("manifest.json");
	const FString DefaultBrowsePath = FPaths::ProjectContentDir();

	TArray<FString> OutFilenames;
	DesktopPlatform->OpenFileDialog(
		ParentWindowWindowHandle,
		Title.ToString(),
		DefaultBrowsePath,
		ManifestFilename,
		FileTypes,
		EFileDialogFlags::None,
		OutFilenames
	);

	if (OutFilenames.Num() == 0)
	{
		return FReply::Unhandled();
	}

	/*
	FTempSettings Settings;
	TSharedPtr<FStructOnScope> StructToDisplay = MakeShareable(new FStructOnScope(FTempSettings::StaticStruct(), (uint8*)&Settings));

	TSharedRef<SKismetInspector> KismetInspector = SNew(SKismetInspector);
	KismetInspector->ShowSingleStruct(StructToDisplay);

	SGenericDialogWidget::FArguments DialogArguments;
	DialogArguments.OnOkPressed_Lambda([&Settings, this, &OutFilenames]()
		{
			if (OutFilenames.Num() > 0)
			{
				ImportCurvesFromFBX(OutFilenames[0]);
			}
		});

	SGenericDialogWidget::OpenDialog(LOCTEXT("Browse", "Browse"), KismetInspector, DialogArguments, true);
	*/

	const FScopedTransaction SetAttributeValueTransaction(NSLOCTEXT("ReactionalBundlePropertyTypeCustomization", "SetAttributeValueTransaction", "Set Bundle Path Name"));
	
	FString RelContentFolderPath = OutFilenames[0];

	if ( FPaths::MakePathRelativeTo(RelContentFolderPath, *FPaths::ProjectContentDir()) )
	{
		FolderPathHandle->SetValue(RelContentFolderPath);
	}

	return FReply::Handled();
}

#pragma optimize ("", on)
#undef LOCTEXT_NAMESPACE
