// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/RangeEnemy.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRangeEnemy() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy();
	MYPROJECT_API UClass* Z_Construct_UClass_ARangedEnemyProjectile_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_ARangeEnemy();
	MYPROJECT_API UClass* Z_Construct_UClass_ARangeEnemy_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void ARangeEnemy::StaticRegisterNativesARangeEnemy()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARangeEnemy);
	UClass* Z_Construct_UClass_ARangeEnemy_NoRegister()
	{
		return ARangeEnemy::StaticClass();
	}
	struct Z_Construct_UClass_ARangeEnemy_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Projectile_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_Projectile;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARangeEnemy_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseEnemy,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARangeEnemy_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARangeEnemy_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "RangeEnemy.h" },
		{ "ModuleRelativePath", "RangeEnemy.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARangeEnemy_Statics::NewProp_Projectile_MetaData[] = {
		{ "Category", "RangeEnemy" },
		{ "ModuleRelativePath", "RangeEnemy.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARangeEnemy_Statics::NewProp_Projectile = { "Projectile", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARangeEnemy, Projectile), Z_Construct_UClass_UClass, Z_Construct_UClass_ARangedEnemyProjectile_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARangeEnemy_Statics::NewProp_Projectile_MetaData), Z_Construct_UClass_ARangeEnemy_Statics::NewProp_Projectile_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARangeEnemy_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARangeEnemy_Statics::NewProp_Projectile,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARangeEnemy_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARangeEnemy>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ARangeEnemy_Statics::ClassParams = {
		&ARangeEnemy::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ARangeEnemy_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ARangeEnemy_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARangeEnemy_Statics::Class_MetaDataParams), Z_Construct_UClass_ARangeEnemy_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARangeEnemy_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ARangeEnemy()
	{
		if (!Z_Registration_Info_UClass_ARangeEnemy.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARangeEnemy.OuterSingleton, Z_Construct_UClass_ARangeEnemy_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ARangeEnemy.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ARangeEnemy>()
	{
		return ARangeEnemy::StaticClass();
	}
	ARangeEnemy::ARangeEnemy() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARangeEnemy);
	ARangeEnemy::~ARangeEnemy() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangeEnemy_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangeEnemy_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ARangeEnemy, ARangeEnemy::StaticClass, TEXT("ARangeEnemy"), &Z_Registration_Info_UClass_ARangeEnemy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARangeEnemy), 2187633954U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangeEnemy_h_1071532648(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangeEnemy_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangeEnemy_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
