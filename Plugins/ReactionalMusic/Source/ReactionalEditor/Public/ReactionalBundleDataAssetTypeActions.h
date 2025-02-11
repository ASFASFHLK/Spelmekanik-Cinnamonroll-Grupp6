/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "AssetTypeActions_Base.h"

class FAssetTypeActions_ReactionalBundleDataAsset : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_ReactionalBundleDataAsset() {}

protected:
	//~ Begin IAssetTypeActions Interface.
	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	//~ End IAssetTypeActions Interface.
};
