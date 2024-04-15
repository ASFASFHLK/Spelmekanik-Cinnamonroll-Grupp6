// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/RangedEnemyProjectile.h"
#include "../../Source/Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRangedEnemyProjectile() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	MYPROJECT_API UClass* Z_Construct_UClass_ARangedEnemyProjectile();
	MYPROJECT_API UClass* Z_Construct_UClass_ARangedEnemyProjectile_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	DEFINE_FUNCTION(ARangedEnemyProjectile::execOnHit)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_hitComp);
		P_GET_OBJECT(AActor,Z_Param_otherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_otherComp);
		P_GET_STRUCT(FVector,Z_Param_normalImpulse);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_hit);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnHit(Z_Param_hitComp,Z_Param_otherActor,Z_Param_otherComp,Z_Param_normalImpulse,Z_Param_Out_hit);
		P_NATIVE_END;
	}
	void ARangedEnemyProjectile::StaticRegisterNativesARangedEnemyProjectile()
	{
		UClass* Class = ARangedEnemyProjectile::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnHit", &ARangedEnemyProjectile::execOnHit },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics
	{
		struct RangedEnemyProjectile_eventOnHit_Parms
		{
			UPrimitiveComponent* hitComp;
			AActor* otherActor;
			UPrimitiveComponent* otherComp;
			FVector normalImpulse;
			FHitResult hit;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_hitComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_hitComp;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_otherActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_otherComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_otherComp;
		static const UECodeGen_Private::FStructPropertyParams NewProp_normalImpulse;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_hit_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_hit;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hitComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hitComp = { "hitComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RangedEnemyProjectile_eventOnHit_Parms, hitComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hitComp_MetaData), Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hitComp_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_otherActor = { "otherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RangedEnemyProjectile_eventOnHit_Parms, otherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_otherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_otherComp = { "otherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RangedEnemyProjectile_eventOnHit_Parms, otherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_otherComp_MetaData), Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_otherComp_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_normalImpulse = { "normalImpulse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RangedEnemyProjectile_eventOnHit_Parms, normalImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hit = { "hit", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RangedEnemyProjectile_eventOnHit_Parms, hit), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hit_MetaData), Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hit_MetaData) }; // 1891709922
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hitComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_otherActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_otherComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_normalImpulse,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::NewProp_hit,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "RangedEnemyProjectile.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARangedEnemyProjectile, nullptr, "OnHit", nullptr, nullptr, Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::RangedEnemyProjectile_eventOnHit_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C40401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::RangedEnemyProjectile_eventOnHit_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ARangedEnemyProjectile_OnHit()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARangedEnemyProjectile_OnHit_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARangedEnemyProjectile);
	UClass* Z_Construct_UClass_ARangedEnemyProjectile_NoRegister()
	{
		return ARangedEnemyProjectile::StaticClass();
	}
	struct Z_Construct_UClass_ARangedEnemyProjectile_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DamageDealt_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DamageDealt;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARangedEnemyProjectile_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARangedEnemyProjectile_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ARangedEnemyProjectile_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ARangedEnemyProjectile_OnHit, "OnHit" }, // 1332463807
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARangedEnemyProjectile_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARangedEnemyProjectile_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "RangedEnemyProjectile.h" },
		{ "ModuleRelativePath", "RangedEnemyProjectile.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARangedEnemyProjectile_Statics::NewProp_DamageDealt_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "RangedEnemyProjectile.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ARangedEnemyProjectile_Statics::NewProp_DamageDealt = { "DamageDealt", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARangedEnemyProjectile, DamageDealt), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARangedEnemyProjectile_Statics::NewProp_DamageDealt_MetaData), Z_Construct_UClass_ARangedEnemyProjectile_Statics::NewProp_DamageDealt_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARangedEnemyProjectile_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARangedEnemyProjectile_Statics::NewProp_DamageDealt,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARangedEnemyProjectile_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARangedEnemyProjectile>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ARangedEnemyProjectile_Statics::ClassParams = {
		&ARangedEnemyProjectile::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ARangedEnemyProjectile_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ARangedEnemyProjectile_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARangedEnemyProjectile_Statics::Class_MetaDataParams), Z_Construct_UClass_ARangedEnemyProjectile_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARangedEnemyProjectile_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ARangedEnemyProjectile()
	{
		if (!Z_Registration_Info_UClass_ARangedEnemyProjectile.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARangedEnemyProjectile.OuterSingleton, Z_Construct_UClass_ARangedEnemyProjectile_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ARangedEnemyProjectile.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ARangedEnemyProjectile>()
	{
		return ARangedEnemyProjectile::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARangedEnemyProjectile);
	ARangedEnemyProjectile::~ARangedEnemyProjectile() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangedEnemyProjectile_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangedEnemyProjectile_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ARangedEnemyProjectile, ARangedEnemyProjectile::StaticClass, TEXT("ARangedEnemyProjectile"), &Z_Registration_Info_UClass_ARangedEnemyProjectile, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARangedEnemyProjectile), 2506631305U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangedEnemyProjectile_h_2054897814(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangedEnemyProjectile_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_RangedEnemyProjectile_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
