// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/BTService_IsStunned.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBTService_IsStunned() {}
// Cross Module References
	AIMODULE_API UClass* Z_Construct_UClass_UBTService();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTService_IsStunned();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTService_IsStunned_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void UBTService_IsStunned::StaticRegisterNativesUBTService_IsStunned()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBTService_IsStunned);
	UClass* Z_Construct_UClass_UBTService_IsStunned_NoRegister()
	{
		return UBTService_IsStunned::StaticClass();
	}
	struct Z_Construct_UClass_UBTService_IsStunned_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBTService_IsStunned_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTService,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_IsStunned_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBTService_IsStunned_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "BTService_IsStunned.h" },
		{ "ModuleRelativePath", "BTService_IsStunned.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBTService_IsStunned_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTService_IsStunned>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTService_IsStunned_Statics::ClassParams = {
		&UBTService_IsStunned::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_IsStunned_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTService_IsStunned_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UBTService_IsStunned()
	{
		if (!Z_Registration_Info_UClass_UBTService_IsStunned.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTService_IsStunned.OuterSingleton, Z_Construct_UClass_UBTService_IsStunned_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBTService_IsStunned.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<UBTService_IsStunned>()
	{
		return UBTService_IsStunned::StaticClass();
	}
	UBTService_IsStunned::UBTService_IsStunned(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBTService_IsStunned);
	UBTService_IsStunned::~UBTService_IsStunned() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_IsStunned_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_IsStunned_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBTService_IsStunned, UBTService_IsStunned::StaticClass, TEXT("UBTService_IsStunned"), &Z_Registration_Info_UClass_UBTService_IsStunned, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTService_IsStunned), 2166082364U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_IsStunned_h_415897690(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_IsStunned_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_IsStunned_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
