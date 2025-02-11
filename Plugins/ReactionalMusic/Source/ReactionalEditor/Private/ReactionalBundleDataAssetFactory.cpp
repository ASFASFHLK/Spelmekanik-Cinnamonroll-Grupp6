/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalBundleDataAssetFactory.h"

#include "AssetTypeCategories.h"
#include "EngineAnalytics.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "EditorFramework/AssetImportData.h"
#include "Editor.h"
#include "ObjectTools.h"
#include "PackageTools.h"
#include "AssetToolsModule.h"
#include "ReactionalEngine.h"
#include "Subsystems/ImportSubsystem.h"

#pragma optimize("", off)

//////////////////////////////////////////////////////////////////////////
// UPaperSpriteSheetImportFactory

UReactionalBundleDataAssetFactory::UReactionalBundleDataAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = false;
	//bEditAfterNew = true;
	SupportedClass = UReactionalBundleDataAsset::StaticClass();

	bEditorImport = true;
	bText = true;

	Formats.Add(TEXT("json; Reactional Manifest JSON file"));
	Formats.Add(TEXT("reactionalpackage; Reactional bundle archive file"));
}

FText UReactionalBundleDataAssetFactory::GetToolTip() const
{
	return NSLOCTEXT("FReactionalEditorModule", "ReactionalImportFactoryDescription", "ReactionalImportFactoryDescription");
}

bool UReactionalBundleDataAssetFactory::FactoryCanImport(const FString& Filename)
{
	FString FileContent;
	if (FFileHelper::LoadFileToString(/*out*/ FileContent, *Filename))
	{
		return true;
		//return FPaperJsonSpriteSheetImporter::CanImportJSON(FileContent);
	}

	return false;
}

UObject* UReactionalBundleDataAssetFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	Flags |= RF_Transactional;

	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPreImport(this, InClass, InParent, InName, Type);

	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");

	const FString FactoryCurrentFilename = UFactory::GetCurrentFilename();
	FString CurrentSourcePath;
	FString FilenameNoExtension;
	FString UnusedExtension;
	FPaths::Split(FactoryCurrentFilename, CurrentSourcePath, FilenameNoExtension, UnusedExtension);

	const FString LongPackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetPathName());

	const FString NameForErrors(InName.ToString());
	const FString FileContent(BufferEnd - Buffer, Buffer);

	FName DataAssetName;
	FString RelContentFolderPath;
	if (FPaths::MakePathRelativeTo(CurrentSourcePath, *FPaths::ProjectContentDir()))
	{
		FString RelLeafPath = FPaths::GetPathLeaf(MoveTemp(CurrentSourcePath));
		DataAssetName = FName(*RelLeafPath);
	}
	else
	{
		return nullptr;
	}

	UReactionalBundleDataAsset* Result = nullptr;

	FString ManifestName = ObjectTools::SanitizeObjectName(InName.ToString());
	FString NewPackageName = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName()) + TEXT("/") + ManifestName;
	UPackage* Package = UPackageTools::FindOrCreatePackageForAssetType(FName(*NewPackageName), UStaticMesh::StaticClass());
	check(Package);
	NewPackageName = Package->GetFullName();
	ManifestName = FPaths::GetBaseFilename(NewPackageName, true);



	UReactionalBundleDataAsset* DataAsset = NewObject<UReactionalBundleDataAsset>(InParent, InName, Flags);
	if ( DataAsset )
	{
		DataAsset->Bundle.BundlePath = RelContentFolderPath;
	}
		//if (Importer.PerformImport(LongPackagePath, Flags, SpriteSheet))
		//{
		//	SpriteSheet->AssetImportData->Update(FactoryCurrentFilename);

	Result = DataAsset;
		//}

	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPostImport(this, Result);

	// Reset the importer to ensure that no leftover data can contaminate future imports.
	//Importer = FPaperJsonSpriteSheetImporter();

	return Result;
}

/*
UReactionalBundleDataAssetFactory::UReactionalBundleDataAssetFactory()
{
	SupportedClass = UReactionalBundleDataAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UReactionalBundleDataAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UReactionalBundleDataAsset>(InParent, InClass, InName, Flags);
}

uint32 UReactionalBundleDataAssetFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Media;
}


bool UReactionalBundleDataAssetFactory::ShouldShowInNewMenu() const
{
	return true;
}
*/

#pragma optimize("", on)
