// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/BTService_PlayerClose.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBTService_PlayerClose() {}
// Cross Module References
	AIMODULE_API UClass* Z_Construct_UClass_UBTService();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTService_PlayerClose();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTService_PlayerClose_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void UBTService_PlayerClose::StaticRegisterNativesUBTService_PlayerClose()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBTService_PlayerClose);
	UClass* Z_Construct_UClass_UBTService_PlayerClose_NoRegister()
	{
		return UBTService_PlayerClose::StaticClass();
	}
	struct Z_Construct_UClass_UBTService_PlayerClose_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBTService_PlayerClose_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTService,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_PlayerClose_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBTService_PlayerClose_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "BTService_PlayerClose.h" },
		{ "ModuleRelativePath", "BTService_PlayerClose.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBTService_PlayerClose_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTService_PlayerClose>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTService_PlayerClose_Statics::ClassParams = {
		&UBTService_PlayerClose::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_PlayerClose_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTService_PlayerClose_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UBTService_PlayerClose()
	{
		if (!Z_Registration_Info_UClass_UBTService_PlayerClose.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTService_PlayerClose.OuterSingleton, Z_Construct_UClass_UBTService_PlayerClose_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBTService_PlayerClose.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<UBTService_PlayerClose>()
	{
		return UBTService_PlayerClose::StaticClass();
	}
	UBTService_PlayerClose::UBTService_PlayerClose(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBTService_PlayerClose);
	UBTService_PlayerClose::~UBTService_PlayerClose() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_PlayerClose_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_PlayerClose_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBTService_PlayerClose, UBTService_PlayerClose::StaticClass, TEXT("UBTService_PlayerClose"), &Z_Registration_Info_UClass_UBTService_PlayerClose, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTService_PlayerClose), 3756281903U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_PlayerClose_h_3568513935(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_PlayerClose_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_PlayerClose_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
