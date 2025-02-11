/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "IDetailCustomization.h"
#include "IPropertyTypeCustomization.h"
#include "ReactionalBundleDataAssetDetailsCustomization.generated.h"

#pragma once

USTRUCT()
struct FTempSettings
{
	GENERATED_USTRUCT_BODY()

	FTempSettings()
		: Scale(1.f)
		, Detail(1)
		, bMergeCurves(false)
	{}

	UPROPERTY(EditAnywhere, Category = "Fbx Import")
	float Scale;

	UPROPERTY(EditAnywhere, Category = "Fbx Import", meta = (UIMin = "1", UIMax = "8"))
	int32 Detail;

	UPROPERTY(EditAnywhere, Category = "Fbx Import")
	bool bMergeCurves;
};

class FReactionalBundlePropertyTypeCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	//~ Begin IPropertyTypeCustomization
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	
	FReply OnBrowsePathClicked();


	//~ End IPropertyTypeCustomization

private:

	/** Handle to the struct property being customized */
	//TSharedPtr<IPropertyHandle> StructPropertyHandle;

	/** Returns the value as FName */
	FString GetFolderPathValue() const;

	/** Sets the value */
	void SetFolderPathValue(FString NewValue);

	/** Requests a refresh of the customization */
	void RequestRefresh();

	/** Refreshes instantly */
	void Refresh();

	/** Property handle for the Name property */
	TSharedPtr<IPropertyHandle> FolderPathHandle;

	TSharedPtr<IPropertyHandle> StructPropertyHandle;

	/** Timer handle set when refresh is requested but not carried out yet */
	FTimerHandle RefreshHandle;
};

class IDetailLayoutBuilder;

class FReactionalBundleDetailCustomization : public IDetailCustomization
{
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	//~ Begin IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;
	virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;

	//~ End IDetailCustomization interface */
private:
	TWeakPtr<IDetailLayoutBuilder> DetailBuilderWeakPtr;
};

