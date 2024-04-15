// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/MeleeEnemy.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMeleeEnemy() {}
// Cross Module References
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy();
	MYPROJECT_API UClass* Z_Construct_UClass_AMeleeEnemy();
	MYPROJECT_API UClass* Z_Construct_UClass_AMeleeEnemy_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void AMeleeEnemy::StaticRegisterNativesAMeleeEnemy()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMeleeEnemy);
	UClass* Z_Construct_UClass_AMeleeEnemy_NoRegister()
	{
		return AMeleeEnemy::StaticClass();
	}
	struct Z_Construct_UClass_AMeleeEnemy_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMeleeEnemy_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseEnemy,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleeEnemy_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMeleeEnemy_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MeleeEnemy.h" },
		{ "ModuleRelativePath", "MeleeEnemy.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMeleeEnemy_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMeleeEnemy>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMeleeEnemy_Statics::ClassParams = {
		&AMeleeEnemy::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleeEnemy_Statics::Class_MetaDataParams), Z_Construct_UClass_AMeleeEnemy_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AMeleeEnemy()
	{
		if (!Z_Registration_Info_UClass_AMeleeEnemy.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMeleeEnemy.OuterSingleton, Z_Construct_UClass_AMeleeEnemy_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMeleeEnemy.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<AMeleeEnemy>()
	{
		return AMeleeEnemy::StaticClass();
	}
	AMeleeEnemy::AMeleeEnemy() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMeleeEnemy);
	AMeleeEnemy::~AMeleeEnemy() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_MeleeEnemy_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_MeleeEnemy_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMeleeEnemy, AMeleeEnemy::StaticClass, TEXT("AMeleeEnemy"), &Z_Registration_Info_UClass_AMeleeEnemy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMeleeEnemy), 1883762763U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_MeleeEnemy_h_76075359(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_MeleeEnemy_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_MeleeEnemy_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
