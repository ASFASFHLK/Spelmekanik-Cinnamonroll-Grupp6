// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/WaterBarrel.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWaterBarrel() {}
// Cross Module References
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseBarrel();
	MYPROJECT_API UClass* Z_Construct_UClass_AWaterBarrel();
	MYPROJECT_API UClass* Z_Construct_UClass_AWaterBarrel_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void AWaterBarrel::StaticRegisterNativesAWaterBarrel()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWaterBarrel);
	UClass* Z_Construct_UClass_AWaterBarrel_NoRegister()
	{
		return AWaterBarrel::StaticClass();
	}
	struct Z_Construct_UClass_AWaterBarrel_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TimeStunned_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeStunned;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWaterBarrel_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseBarrel,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWaterBarrel_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWaterBarrel_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "WaterBarrel.h" },
		{ "ModuleRelativePath", "WaterBarrel.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWaterBarrel_Statics::NewProp_TimeStunned_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "WaterBarrel.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AWaterBarrel_Statics::NewProp_TimeStunned = { "TimeStunned", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWaterBarrel, TimeStunned), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWaterBarrel_Statics::NewProp_TimeStunned_MetaData), Z_Construct_UClass_AWaterBarrel_Statics::NewProp_TimeStunned_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWaterBarrel_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaterBarrel_Statics::NewProp_TimeStunned,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWaterBarrel_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWaterBarrel>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWaterBarrel_Statics::ClassParams = {
		&AWaterBarrel::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AWaterBarrel_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AWaterBarrel_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWaterBarrel_Statics::Class_MetaDataParams), Z_Construct_UClass_AWaterBarrel_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWaterBarrel_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AWaterBarrel()
	{
		if (!Z_Registration_Info_UClass_AWaterBarrel.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWaterBarrel.OuterSingleton, Z_Construct_UClass_AWaterBarrel_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWaterBarrel.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<AWaterBarrel>()
	{
		return AWaterBarrel::StaticClass();
	}
	AWaterBarrel::AWaterBarrel() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWaterBarrel);
	AWaterBarrel::~AWaterBarrel() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_WaterBarrel_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_WaterBarrel_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWaterBarrel, AWaterBarrel::StaticClass, TEXT("AWaterBarrel"), &Z_Registration_Info_UClass_AWaterBarrel, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWaterBarrel), 3878753948U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_WaterBarrel_h_3343525486(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_WaterBarrel_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_WaterBarrel_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
