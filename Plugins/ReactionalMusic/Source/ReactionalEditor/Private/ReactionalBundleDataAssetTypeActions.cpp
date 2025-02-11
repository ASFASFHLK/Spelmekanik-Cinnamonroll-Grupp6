/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/


#include "ReactionalBundleDataAssetTypeActions.h"
#include "ReactionalEngine.h"

#define LOCTEXT_NAMESPACE "FReactionalEditorModule"

UClass* FAssetTypeActions_ReactionalBundleDataAsset::GetSupportedClass() const
{
	return UReactionalBundleDataAsset::StaticClass();
}

FText FAssetTypeActions_ReactionalBundleDataAsset::GetName() const
{
	return LOCTEXT("AssetTypeActions_ReactionalBundleDataAssetBuilder", "ReactionalBundle"); 
}

FColor FAssetTypeActions_ReactionalBundleDataAsset::GetTypeColor() const
{
	return FColor(128, 128, 128); 
}

uint32 FAssetTypeActions_ReactionalBundleDataAsset::GetCategories()
{
	return EAssetTypeCategories::Misc; 
}

#undef LOCTEXT_NAMESPACE
