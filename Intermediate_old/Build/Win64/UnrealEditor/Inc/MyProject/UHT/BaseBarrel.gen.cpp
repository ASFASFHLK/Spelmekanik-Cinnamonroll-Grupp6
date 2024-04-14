// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/BaseBarrel.h"
#include "../../Source/Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseBarrel() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UDamageType_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseBarrel();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseBarrel_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_UHealthComp_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void ABaseBarrel::StaticRegisterNativesABaseBarrel()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABaseBarrel);
	UClass* Z_Construct_UClass_ABaseBarrel_NoRegister()
	{
		return ABaseBarrel::StaticClass();
	}
	struct Z_Construct_UClass_ABaseBarrel_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HealthComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_HealthComp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExplosionRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ExplosionRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DamageType_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_DamageType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DamageDealt_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DamageDealt;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Exploded_MetaData[];
#endif
		static void NewProp_Exploded_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_Exploded;
		static const UECodeGen_Private::FStructPropertyParams NewProp_HitResults_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HitResults_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_HitResults;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABaseBarrel_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseBarrel_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BaseBarrel.h" },
		{ "ModuleRelativePath", "BaseBarrel.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HealthComp_MetaData[] = {
		{ "Category", "BaseBarrel" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "BaseBarrel.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HealthComp = { "HealthComp", nullptr, (EPropertyFlags)0x002008000009001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseBarrel, HealthComp), Z_Construct_UClass_UHealthComp_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HealthComp_MetaData), Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HealthComp_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseBarrel_Statics::NewProp_ExplosionRadius_MetaData[] = {
		{ "Category", "Explosion" },
		{ "ModuleRelativePath", "BaseBarrel.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABaseBarrel_Statics::NewProp_ExplosionRadius = { "ExplosionRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseBarrel, ExplosionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::NewProp_ExplosionRadius_MetaData), Z_Construct_UClass_ABaseBarrel_Statics::NewProp_ExplosionRadius_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageType_MetaData[] = {
		{ "Category", "Explosion" },
		{ "ModuleRelativePath", "BaseBarrel.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageType = { "DamageType", nullptr, (EPropertyFlags)0x0044000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseBarrel, DamageType), Z_Construct_UClass_UClass, Z_Construct_UClass_UDamageType_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageType_MetaData), Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageType_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageDealt_MetaData[] = {
		{ "Category", "Explosion" },
		{ "ModuleRelativePath", "BaseBarrel.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageDealt = { "DamageDealt", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseBarrel, DamageDealt), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageDealt_MetaData), Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageDealt_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseBarrel_Statics::NewProp_Exploded_MetaData[] = {
		{ "ModuleRelativePath", "BaseBarrel.h" },
	};
#endif
	void Z_Construct_UClass_ABaseBarrel_Statics::NewProp_Exploded_SetBit(void* Obj)
	{
		((ABaseBarrel*)Obj)->Exploded = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABaseBarrel_Statics::NewProp_Exploded = { "Exploded", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABaseBarrel), &Z_Construct_UClass_ABaseBarrel_Statics::NewProp_Exploded_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::NewProp_Exploded_MetaData), Z_Construct_UClass_ABaseBarrel_Statics::NewProp_Exploded_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HitResults_Inner = { "HitResults", nullptr, (EPropertyFlags)0x0000008000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(0, nullptr) }; // 1891709922
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HitResults_MetaData[] = {
		{ "ModuleRelativePath", "BaseBarrel.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HitResults = { "HitResults", nullptr, (EPropertyFlags)0x0040008000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseBarrel, HitResults), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HitResults_MetaData), Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HitResults_MetaData) }; // 1891709922
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABaseBarrel_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HealthComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseBarrel_Statics::NewProp_ExplosionRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseBarrel_Statics::NewProp_DamageDealt,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseBarrel_Statics::NewProp_Exploded,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HitResults_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseBarrel_Statics::NewProp_HitResults,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABaseBarrel_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABaseBarrel>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABaseBarrel_Statics::ClassParams = {
		&ABaseBarrel::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABaseBarrel_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::Class_MetaDataParams), Z_Construct_UClass_ABaseBarrel_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseBarrel_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ABaseBarrel()
	{
		if (!Z_Registration_Info_UClass_ABaseBarrel.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABaseBarrel.OuterSingleton, Z_Construct_UClass_ABaseBarrel_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABaseBarrel.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ABaseBarrel>()
	{
		return ABaseBarrel::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABaseBarrel);
	ABaseBarrel::~ABaseBarrel() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseBarrel_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseBarrel_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABaseBarrel, ABaseBarrel::StaticClass, TEXT("ABaseBarrel"), &Z_Registration_Info_UClass_ABaseBarrel, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABaseBarrel), 1921347272U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseBarrel_h_619181463(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseBarrel_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseBarrel_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
