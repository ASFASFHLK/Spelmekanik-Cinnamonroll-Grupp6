// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/GunBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGunBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UMeshComponent_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_AGunBase();
	MYPROJECT_API UClass* Z_Construct_UClass_AGunBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void AGunBase::StaticRegisterNativesAGunBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGunBase);
	UClass* Z_Construct_UClass_AGunBase_NoRegister()
	{
		return AGunBase::StaticClass();
	}
	struct Z_Construct_UClass_AGunBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GunMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_GunMesh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Damage_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Damage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FireRate_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FireRate;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGunBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGunBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGunBase_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GunBase.h" },
		{ "ModuleRelativePath", "GunBase.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGunBase_Statics::NewProp_GunMesh_MetaData[] = {
		{ "Category", "GunBase" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GunBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGunBase_Statics::NewProp_GunMesh = { "GunMesh", nullptr, (EPropertyFlags)0x0020080000090009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGunBase, GunMesh), Z_Construct_UClass_UMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGunBase_Statics::NewProp_GunMesh_MetaData), Z_Construct_UClass_AGunBase_Statics::NewProp_GunMesh_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGunBase_Statics::NewProp_Damage_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "GunBase.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AGunBase_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGunBase, Damage), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGunBase_Statics::NewProp_Damage_MetaData), Z_Construct_UClass_AGunBase_Statics::NewProp_Damage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGunBase_Statics::NewProp_FireRate_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "GunBase.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGunBase_Statics::NewProp_FireRate = { "FireRate", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGunBase, FireRate), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGunBase_Statics::NewProp_FireRate_MetaData), Z_Construct_UClass_AGunBase_Statics::NewProp_FireRate_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGunBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGunBase_Statics::NewProp_GunMesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGunBase_Statics::NewProp_Damage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGunBase_Statics::NewProp_FireRate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGunBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGunBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AGunBase_Statics::ClassParams = {
		&AGunBase::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGunBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGunBase_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGunBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AGunBase_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGunBase_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AGunBase()
	{
		if (!Z_Registration_Info_UClass_AGunBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGunBase.OuterSingleton, Z_Construct_UClass_AGunBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AGunBase.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<AGunBase>()
	{
		return AGunBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGunBase);
	AGunBase::~AGunBase() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_GunBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_GunBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AGunBase, AGunBase::StaticClass, TEXT("AGunBase"), &Z_Registration_Info_UClass_AGunBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGunBase), 3650423687U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_GunBase_h_1857040202(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_GunBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_GunBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
