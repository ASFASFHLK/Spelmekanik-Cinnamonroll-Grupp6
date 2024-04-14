// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/ExplosiveEnemy.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExplosiveEnemy() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_UDamageType_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy();
	MYPROJECT_API UClass* Z_Construct_UClass_AExplosiveEnemy();
	MYPROJECT_API UClass* Z_Construct_UClass_AExplosiveEnemy_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void AExplosiveEnemy::StaticRegisterNativesAExplosiveEnemy()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AExplosiveEnemy);
	UClass* Z_Construct_UClass_AExplosiveEnemy_NoRegister()
	{
		return AExplosiveEnemy::StaticClass();
	}
	struct Z_Construct_UClass_AExplosiveEnemy_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DamageType_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_DamageType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExplosionRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ExplosionRadius;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AExplosiveEnemy_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseEnemy,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AExplosiveEnemy_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AExplosiveEnemy_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "ExplosiveEnemy.h" },
		{ "ModuleRelativePath", "ExplosiveEnemy.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_DamageType_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "ExplosiveEnemy.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_DamageType = { "DamageType", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AExplosiveEnemy, DamageType), Z_Construct_UClass_UClass, Z_Construct_UClass_UDamageType_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_DamageType_MetaData), Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_DamageType_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_ExplosionRadius_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "ExplosiveEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_ExplosionRadius = { "ExplosionRadius", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AExplosiveEnemy, ExplosionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_ExplosionRadius_MetaData), Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_ExplosionRadius_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AExplosiveEnemy_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_DamageType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AExplosiveEnemy_Statics::NewProp_ExplosionRadius,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AExplosiveEnemy_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AExplosiveEnemy>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AExplosiveEnemy_Statics::ClassParams = {
		&AExplosiveEnemy::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AExplosiveEnemy_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AExplosiveEnemy_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AExplosiveEnemy_Statics::Class_MetaDataParams), Z_Construct_UClass_AExplosiveEnemy_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AExplosiveEnemy_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AExplosiveEnemy()
	{
		if (!Z_Registration_Info_UClass_AExplosiveEnemy.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AExplosiveEnemy.OuterSingleton, Z_Construct_UClass_AExplosiveEnemy_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AExplosiveEnemy.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<AExplosiveEnemy>()
	{
		return AExplosiveEnemy::StaticClass();
	}
	AExplosiveEnemy::AExplosiveEnemy() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AExplosiveEnemy);
	AExplosiveEnemy::~AExplosiveEnemy() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ExplosiveEnemy_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ExplosiveEnemy_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AExplosiveEnemy, AExplosiveEnemy::StaticClass, TEXT("AExplosiveEnemy"), &Z_Registration_Info_UClass_AExplosiveEnemy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AExplosiveEnemy), 1461182359U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ExplosiveEnemy_h_1942781415(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ExplosiveEnemy_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ExplosiveEnemy_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
