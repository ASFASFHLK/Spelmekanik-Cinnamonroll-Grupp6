// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/BTTask_DoAttack.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBTTask_DoAttack() {}
// Cross Module References
	AIMODULE_API UClass* Z_Construct_UClass_UBTTaskNode();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTTask_DoAttack();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTTask_DoAttack_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void UBTTask_DoAttack::StaticRegisterNativesUBTTask_DoAttack()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBTTask_DoAttack);
	UClass* Z_Construct_UClass_UBTTask_DoAttack_NoRegister()
	{
		return UBTTask_DoAttack::StaticClass();
	}
	struct Z_Construct_UClass_UBTTask_DoAttack_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Enemy_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Enemy;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBTTask_DoAttack_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTTaskNode,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_DoAttack_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBTTask_DoAttack_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "BTTask_DoAttack.h" },
		{ "ModuleRelativePath", "BTTask_DoAttack.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBTTask_DoAttack_Statics::NewProp_Enemy_MetaData[] = {
		{ "ModuleRelativePath", "BTTask_DoAttack.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBTTask_DoAttack_Statics::NewProp_Enemy = { "Enemy", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTTask_DoAttack, Enemy), Z_Construct_UClass_ABaseEnemy_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_DoAttack_Statics::NewProp_Enemy_MetaData), Z_Construct_UClass_UBTTask_DoAttack_Statics::NewProp_Enemy_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBTTask_DoAttack_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTTask_DoAttack_Statics::NewProp_Enemy,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBTTask_DoAttack_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTTask_DoAttack>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTTask_DoAttack_Statics::ClassParams = {
		&UBTTask_DoAttack::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBTTask_DoAttack_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_DoAttack_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_DoAttack_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTTask_DoAttack_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTTask_DoAttack_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UBTTask_DoAttack()
	{
		if (!Z_Registration_Info_UClass_UBTTask_DoAttack.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTTask_DoAttack.OuterSingleton, Z_Construct_UClass_UBTTask_DoAttack_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBTTask_DoAttack.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<UBTTask_DoAttack>()
	{
		return UBTTask_DoAttack::StaticClass();
	}
	UBTTask_DoAttack::UBTTask_DoAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBTTask_DoAttack);
	UBTTask_DoAttack::~UBTTask_DoAttack() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTTask_DoAttack_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTTask_DoAttack_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBTTask_DoAttack, UBTTask_DoAttack::StaticClass, TEXT("UBTTask_DoAttack"), &Z_Registration_Info_UClass_UBTTask_DoAttack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTTask_DoAttack), 4221615860U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTTask_DoAttack_h_3430733041(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTTask_DoAttack_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTTask_DoAttack_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
