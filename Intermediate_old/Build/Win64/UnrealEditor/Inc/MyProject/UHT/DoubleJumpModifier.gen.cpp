// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/DoubleJumpModifier.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDoubleJumpModifier() {}
// Cross Module References
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseModifier();
	MYPROJECT_API UClass* Z_Construct_UClass_ADoubleJumpModifier();
	MYPROJECT_API UClass* Z_Construct_UClass_ADoubleJumpModifier_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void ADoubleJumpModifier::StaticRegisterNativesADoubleJumpModifier()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADoubleJumpModifier);
	UClass* Z_Construct_UClass_ADoubleJumpModifier_NoRegister()
	{
		return ADoubleJumpModifier::StaticClass();
	}
	struct Z_Construct_UClass_ADoubleJumpModifier_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NumberOfJumps_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NumberOfJumps;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OriginalNumberOfJumps_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_OriginalNumberOfJumps;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADoubleJumpModifier_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseModifier,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADoubleJumpModifier_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADoubleJumpModifier_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "DoubleJumpModifier.h" },
		{ "ModuleRelativePath", "DoubleJumpModifier.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_NumberOfJumps_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "DoubleJumpModifier.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_NumberOfJumps = { "NumberOfJumps", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADoubleJumpModifier, NumberOfJumps), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_NumberOfJumps_MetaData), Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_NumberOfJumps_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_OriginalNumberOfJumps_MetaData[] = {
		{ "ModuleRelativePath", "DoubleJumpModifier.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_OriginalNumberOfJumps = { "OriginalNumberOfJumps", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADoubleJumpModifier, OriginalNumberOfJumps), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_OriginalNumberOfJumps_MetaData), Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_OriginalNumberOfJumps_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADoubleJumpModifier_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_NumberOfJumps,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADoubleJumpModifier_Statics::NewProp_OriginalNumberOfJumps,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADoubleJumpModifier_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADoubleJumpModifier>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ADoubleJumpModifier_Statics::ClassParams = {
		&ADoubleJumpModifier::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ADoubleJumpModifier_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ADoubleJumpModifier_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADoubleJumpModifier_Statics::Class_MetaDataParams), Z_Construct_UClass_ADoubleJumpModifier_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADoubleJumpModifier_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ADoubleJumpModifier()
	{
		if (!Z_Registration_Info_UClass_ADoubleJumpModifier.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADoubleJumpModifier.OuterSingleton, Z_Construct_UClass_ADoubleJumpModifier_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ADoubleJumpModifier.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ADoubleJumpModifier>()
	{
		return ADoubleJumpModifier::StaticClass();
	}
	ADoubleJumpModifier::ADoubleJumpModifier() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADoubleJumpModifier);
	ADoubleJumpModifier::~ADoubleJumpModifier() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DoubleJumpModifier_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DoubleJumpModifier_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ADoubleJumpModifier, ADoubleJumpModifier::StaticClass, TEXT("ADoubleJumpModifier"), &Z_Registration_Info_UClass_ADoubleJumpModifier, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADoubleJumpModifier), 3159432373U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DoubleJumpModifier_h_3277150812(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DoubleJumpModifier_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DoubleJumpModifier_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
