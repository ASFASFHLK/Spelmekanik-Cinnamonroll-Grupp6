// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/BaseModifier.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseModifier() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseModifier();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseModifier_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void ABaseModifier::StaticRegisterNativesABaseModifier()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABaseModifier);
	UClass* Z_Construct_UClass_ABaseModifier_NoRegister()
	{
		return ABaseModifier::StaticClass();
	}
	struct Z_Construct_UClass_ABaseModifier_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlayerCharacter_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerCharacter;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABaseModifier_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseModifier_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseModifier_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BaseModifier.h" },
		{ "ModuleRelativePath", "BaseModifier.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseModifier_Statics::NewProp_PlayerCharacter_MetaData[] = {
		{ "ModuleRelativePath", "BaseModifier.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABaseModifier_Statics::NewProp_PlayerCharacter = { "PlayerCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseModifier, PlayerCharacter), Z_Construct_UClass_APlayerCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseModifier_Statics::NewProp_PlayerCharacter_MetaData), Z_Construct_UClass_ABaseModifier_Statics::NewProp_PlayerCharacter_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABaseModifier_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseModifier_Statics::NewProp_PlayerCharacter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABaseModifier_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABaseModifier>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABaseModifier_Statics::ClassParams = {
		&ABaseModifier::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ABaseModifier_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ABaseModifier_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseModifier_Statics::Class_MetaDataParams), Z_Construct_UClass_ABaseModifier_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseModifier_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ABaseModifier()
	{
		if (!Z_Registration_Info_UClass_ABaseModifier.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABaseModifier.OuterSingleton, Z_Construct_UClass_ABaseModifier_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABaseModifier.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ABaseModifier>()
	{
		return ABaseModifier::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABaseModifier);
	ABaseModifier::~ABaseModifier() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseModifier_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseModifier_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABaseModifier, ABaseModifier::StaticClass, TEXT("ABaseModifier"), &Z_Registration_Info_UClass_ABaseModifier, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABaseModifier), 372643882U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseModifier_h_2997718141(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseModifier_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseModifier_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
