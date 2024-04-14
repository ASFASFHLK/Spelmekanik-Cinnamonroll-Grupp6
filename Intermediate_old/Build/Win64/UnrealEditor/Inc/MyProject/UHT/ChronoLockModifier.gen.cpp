// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/ChronoLockModifier.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeChronoLockModifier() {}
// Cross Module References
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseModifier();
	MYPROJECT_API UClass* Z_Construct_UClass_AChronoLockModifier();
	MYPROJECT_API UClass* Z_Construct_UClass_AChronoLockModifier_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	void AChronoLockModifier::StaticRegisterNativesAChronoLockModifier()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AChronoLockModifier);
	UClass* Z_Construct_UClass_AChronoLockModifier_NoRegister()
	{
		return AChronoLockModifier::StaticClass();
	}
	struct Z_Construct_UClass_AChronoLockModifier_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SlowDownAmount_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_SlowDownAmount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AmountOfTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AmountOfTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CurrentTimer_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentTimer;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsActivated_MetaData[];
#endif
		static void NewProp_IsActivated_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsActivated;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AdjustedTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AdjustedTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IaSpecialAbility_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IaSpecialAbility;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AChronoLockModifier_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseModifier,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChronoLockModifier_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "ChronoLockModifier.h" },
		{ "ModuleRelativePath", "ChronoLockModifier.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_SlowDownAmount_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "ChronoLockModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_SlowDownAmount = { "SlowDownAmount", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AChronoLockModifier, SlowDownAmount), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_SlowDownAmount_MetaData), Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_SlowDownAmount_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AmountOfTime_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "ChronoLockModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AmountOfTime = { "AmountOfTime", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AChronoLockModifier, AmountOfTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AmountOfTime_MetaData), Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AmountOfTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_CurrentTimer_MetaData[] = {
		{ "ModuleRelativePath", "ChronoLockModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_CurrentTimer = { "CurrentTimer", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AChronoLockModifier, CurrentTimer), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_CurrentTimer_MetaData), Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_CurrentTimer_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IsActivated_MetaData[] = {
		{ "ModuleRelativePath", "ChronoLockModifier.h" },
	};
#endif
	void Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IsActivated_SetBit(void* Obj)
	{
		((AChronoLockModifier*)Obj)->IsActivated = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IsActivated = { "IsActivated", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AChronoLockModifier), &Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IsActivated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IsActivated_MetaData), Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IsActivated_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AdjustedTime_MetaData[] = {
		{ "ModuleRelativePath", "ChronoLockModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AdjustedTime = { "AdjustedTime", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AChronoLockModifier, AdjustedTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AdjustedTime_MetaData), Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AdjustedTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IaSpecialAbility_MetaData[] = {
		{ "Category", "Ability" },
		{ "ModuleRelativePath", "ChronoLockModifier.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IaSpecialAbility = { "IaSpecialAbility", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AChronoLockModifier, IaSpecialAbility), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IaSpecialAbility_MetaData), Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IaSpecialAbility_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AChronoLockModifier_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_SlowDownAmount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AmountOfTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_CurrentTimer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IsActivated,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_AdjustedTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChronoLockModifier_Statics::NewProp_IaSpecialAbility,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AChronoLockModifier_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AChronoLockModifier>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AChronoLockModifier_Statics::ClassParams = {
		&AChronoLockModifier::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AChronoLockModifier_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::Class_MetaDataParams), Z_Construct_UClass_AChronoLockModifier_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AChronoLockModifier_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AChronoLockModifier()
	{
		if (!Z_Registration_Info_UClass_AChronoLockModifier.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AChronoLockModifier.OuterSingleton, Z_Construct_UClass_AChronoLockModifier_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AChronoLockModifier.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<AChronoLockModifier>()
	{
		return AChronoLockModifier::StaticClass();
	}
	AChronoLockModifier::AChronoLockModifier() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AChronoLockModifier);
	AChronoLockModifier::~AChronoLockModifier() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ChronoLockModifier_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ChronoLockModifier_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AChronoLockModifier, AChronoLockModifier::StaticClass, TEXT("AChronoLockModifier"), &Z_Registration_Info_UClass_AChronoLockModifier, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AChronoLockModifier), 649284115U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ChronoLockModifier_h_2985510669(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ChronoLockModifier_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ChronoLockModifier_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
