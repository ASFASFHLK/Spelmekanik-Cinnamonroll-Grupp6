/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "Factories/Factory.h"
#include "ReactionalBundleDataAssetFactory.generated.h"

UCLASS(hidecategories=Object)
class UReactionalBundleDataAssetFactory
	: public UFactory
{
	GENERATED_UCLASS_BODY()

public:

	UReactionalBundleDataAssetFactory();

	virtual UObject* ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled) override { return nullptr; }
	virtual FText GetToolTip() const override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;

	//virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	//virtual uint32 GetMenuCategories() const override;
	//virtual bool ShouldShowInNewMenu() const override;
};