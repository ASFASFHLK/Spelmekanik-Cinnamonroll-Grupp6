// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/BTService_CheckIfStunned.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBTService_CheckIfStunned() {}
// Cross Module References
	AIMODULE_API UClass* Z_Construct_UClass_UBTService();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTService_CheckIfStunned();
	MYPROJECT_API UClass* Z_Construct_UClass_UBTService_CheckIfStunned_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void UBTService_CheckIfStunned::StaticRegisterNativesUBTService_CheckIfStunned()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBTService_CheckIfStunned);
	UClass* Z_Construct_UClass_UBTService_CheckIfStunned_NoRegister()
	{
		return UBTService_CheckIfStunned::StaticClass();
	}
	struct Z_Construct_UClass_UBTService_CheckIfStunned_Statics
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
	UObject* (*const Z_Construct_UClass_UBTService_CheckIfStunned_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBTService,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_CheckIfStunned_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBTService_CheckIfStunned_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "BTService_CheckIfStunned.h" },
		{ "ModuleRelativePath", "BTService_CheckIfStunned.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBTService_CheckIfStunned_Statics::NewProp_Enemy_MetaData[] = {
		{ "ModuleRelativePath", "BTService_CheckIfStunned.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBTService_CheckIfStunned_Statics::NewProp_Enemy = { "Enemy", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBTService_CheckIfStunned, Enemy), Z_Construct_UClass_ABaseEnemy_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_CheckIfStunned_Statics::NewProp_Enemy_MetaData), Z_Construct_UClass_UBTService_CheckIfStunned_Statics::NewProp_Enemy_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBTService_CheckIfStunned_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBTService_CheckIfStunned_Statics::NewProp_Enemy,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBTService_CheckIfStunned_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBTService_CheckIfStunned>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBTService_CheckIfStunned_Statics::ClassParams = {
		&UBTService_CheckIfStunned::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBTService_CheckIfStunned_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_CheckIfStunned_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_CheckIfStunned_Statics::Class_MetaDataParams), Z_Construct_UClass_UBTService_CheckIfStunned_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBTService_CheckIfStunned_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UBTService_CheckIfStunned()
	{
		if (!Z_Registration_Info_UClass_UBTService_CheckIfStunned.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBTService_CheckIfStunned.OuterSingleton, Z_Construct_UClass_UBTService_CheckIfStunned_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBTService_CheckIfStunned.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<UBTService_CheckIfStunned>()
	{
		return UBTService_CheckIfStunned::StaticClass();
	}
	UBTService_CheckIfStunned::UBTService_CheckIfStunned(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBTService_CheckIfStunned);
	UBTService_CheckIfStunned::~UBTService_CheckIfStunned() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_CheckIfStunned_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_CheckIfStunned_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBTService_CheckIfStunned, UBTService_CheckIfStunned::StaticClass, TEXT("UBTService_CheckIfStunned"), &Z_Registration_Info_UClass_UBTService_CheckIfStunned, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBTService_CheckIfStunned), 4272465334U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_CheckIfStunned_h_2308603620(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_CheckIfStunned_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BTService_CheckIfStunned_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS