// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/DashModifier.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDashModifier() {}
// Cross Module References
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseModifier();
	MYPROJECT_API UClass* Z_Construct_UClass_ADashModifier();
	MYPROJECT_API UClass* Z_Construct_UClass_ADashModifier_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void ADashModifier::StaticRegisterNativesADashModifier()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADashModifier);
	UClass* Z_Construct_UClass_ADashModifier_NoRegister()
	{
		return ADashModifier::StaticClass();
	}
	struct Z_Construct_UClass_ADashModifier_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DashDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DashDistance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsDashing_MetaData[];
#endif
		static void NewProp_IsDashing_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsDashing;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DashCoolDown_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DashCoolDown;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Timer_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Timer;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADashModifier_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseModifier,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADashModifier_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "DashModifier.h" },
		{ "ModuleRelativePath", "DashModifier.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADashModifier_Statics::NewProp_DashDistance_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "DashModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADashModifier_Statics::NewProp_DashDistance = { "DashDistance", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADashModifier, DashDistance), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::NewProp_DashDistance_MetaData), Z_Construct_UClass_ADashModifier_Statics::NewProp_DashDistance_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADashModifier_Statics::NewProp_IsDashing_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "DashModifier.h" },
	};
#endif
	void Z_Construct_UClass_ADashModifier_Statics::NewProp_IsDashing_SetBit(void* Obj)
	{
		((ADashModifier*)Obj)->IsDashing = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADashModifier_Statics::NewProp_IsDashing = { "IsDashing", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ADashModifier), &Z_Construct_UClass_ADashModifier_Statics::NewProp_IsDashing_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::NewProp_IsDashing_MetaData), Z_Construct_UClass_ADashModifier_Statics::NewProp_IsDashing_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADashModifier_Statics::NewProp_DashCoolDown_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "DashModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADashModifier_Statics::NewProp_DashCoolDown = { "DashCoolDown", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADashModifier, DashCoolDown), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::NewProp_DashCoolDown_MetaData), Z_Construct_UClass_ADashModifier_Statics::NewProp_DashCoolDown_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADashModifier_Statics::NewProp_Timer_MetaData[] = {
		{ "ModuleRelativePath", "DashModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ADashModifier_Statics::NewProp_Timer = { "Timer", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADashModifier, Timer), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::NewProp_Timer_MetaData), Z_Construct_UClass_ADashModifier_Statics::NewProp_Timer_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADashModifier_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADashModifier_Statics::NewProp_DashDistance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADashModifier_Statics::NewProp_IsDashing,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADashModifier_Statics::NewProp_DashCoolDown,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADashModifier_Statics::NewProp_Timer,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADashModifier_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADashModifier>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ADashModifier_Statics::ClassParams = {
		&ADashModifier::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ADashModifier_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::Class_MetaDataParams), Z_Construct_UClass_ADashModifier_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADashModifier_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ADashModifier()
	{
		if (!Z_Registration_Info_UClass_ADashModifier.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADashModifier.OuterSingleton, Z_Construct_UClass_ADashModifier_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ADashModifier.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ADashModifier>()
	{
		return ADashModifier::StaticClass();
	}
	ADashModifier::ADashModifier() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADashModifier);
	ADashModifier::~ADashModifier() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DashModifier_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DashModifier_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ADashModifier, ADashModifier::StaticClass, TEXT("ADashModifier"), &Z_Registration_Info_UClass_ADashModifier, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADashModifier), 2639619621U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DashModifier_h_604132735(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DashModifier_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DashModifier_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
