// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/EnemySpawner.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemySpawner() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	MYPROJECT_API UClass* Z_Construct_UClass_AEnemySpawner();
	MYPROJECT_API UClass* Z_Construct_UClass_AEnemySpawner_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void AEnemySpawner::StaticRegisterNativesAEnemySpawner()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemySpawner);
	UClass* Z_Construct_UClass_AEnemySpawner_NoRegister()
	{
		return AEnemySpawner::StaticClass();
	}
	struct Z_Construct_UClass_AEnemySpawner_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemySpawner_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemySpawner_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemySpawner_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EnemySpawner.h" },
		{ "ModuleRelativePath", "EnemySpawner.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemySpawner_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemySpawner>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemySpawner_Statics::ClassParams = {
		&AEnemySpawner::StaticClass,
		"Engine",
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemySpawner_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemySpawner_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AEnemySpawner()
	{
		if (!Z_Registration_Info_UClass_AEnemySpawner.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemySpawner.OuterSingleton, Z_Construct_UClass_AEnemySpawner_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AEnemySpawner.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<AEnemySpawner>()
	{
		return AEnemySpawner::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemySpawner);
	AEnemySpawner::~AEnemySpawner() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_EnemySpawner_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_EnemySpawner_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AEnemySpawner, AEnemySpawner::StaticClass, TEXT("AEnemySpawner"), &Z_Registration_Info_UClass_AEnemySpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemySpawner), 3636545038U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_EnemySpawner_h_806645392(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_EnemySpawner_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_EnemySpawner_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
