// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/BaseEnemy.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseEnemy() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseCharacter();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy_NoRegister();
	MYPROJECT_API UFunction* Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_MyProject, nullptr, "OnDeath__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FOnDeath_DelegateWrapper(const FScriptDelegate& OnDeath)
{
	OnDeath.ProcessDelegate<UObject>(NULL);
}
	DEFINE_FUNCTION(ABaseEnemy::execGetCurrentTarget)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(AActor**)Z_Param__Result=P_THIS->GetCurrentTarget();
		P_NATIVE_END;
	}
	void ABaseEnemy::StaticRegisterNativesABaseEnemy()
	{
		UClass* Class = ABaseEnemy::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetCurrentTarget", &ABaseEnemy::execGetCurrentTarget },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics
	{
		struct BaseEnemy_eventGetCurrentTarget_Parms
		{
			AActor* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BaseEnemy_eventGetCurrentTarget_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ABaseEnemy, nullptr, "GetCurrentTarget", nullptr, nullptr, Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::PropPointers), sizeof(Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::BaseEnemy_eventGetCurrentTarget_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::BaseEnemy_eventGetCurrentTarget_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABaseEnemy);
	UClass* Z_Construct_UClass_ABaseEnemy_NoRegister()
	{
		return ABaseEnemy::StaticClass();
	}
	struct Z_Construct_UClass_ABaseEnemy_Statics
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
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CurrentTarget_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentTarget;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AggroRange_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AggroRange;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackCooldown_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackCooldown;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TargetIsCloseRange_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_TargetIsCloseRange;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CurrentAttackCooldown_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentAttackCooldown;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABaseEnemy_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ABaseCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ABaseEnemy_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ABaseEnemy_GetCurrentTarget, "GetCurrentTarget" }, // 323610792
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemy_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "BaseEnemy.h" },
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemy_Statics::NewProp_DamageDealt_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABaseEnemy_Statics::NewProp_DamageDealt = { "DamageDealt", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseEnemy, DamageDealt), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::NewProp_DamageDealt_MetaData), Z_Construct_UClass_ABaseEnemy_Statics::NewProp_DamageDealt_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentTarget_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentTarget = { "CurrentTarget", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseEnemy, CurrentTarget), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentTarget_MetaData), Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentTarget_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AggroRange_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AggroRange = { "AggroRange", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseEnemy, AggroRange), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AggroRange_MetaData), Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AggroRange_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AttackCooldown_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AttackCooldown = { "AttackCooldown", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseEnemy, AttackCooldown), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AttackCooldown_MetaData), Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AttackCooldown_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemy_Statics::NewProp_TargetIsCloseRange_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABaseEnemy_Statics::NewProp_TargetIsCloseRange = { "TargetIsCloseRange", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseEnemy, TargetIsCloseRange), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::NewProp_TargetIsCloseRange_MetaData), Z_Construct_UClass_ABaseEnemy_Statics::NewProp_TargetIsCloseRange_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentAttackCooldown_MetaData[] = {
		{ "ModuleRelativePath", "BaseEnemy.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentAttackCooldown = { "CurrentAttackCooldown", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABaseEnemy, CurrentAttackCooldown), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentAttackCooldown_MetaData), Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentAttackCooldown_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABaseEnemy_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnemy_Statics::NewProp_DamageDealt,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentTarget,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AggroRange,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnemy_Statics::NewProp_AttackCooldown,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnemy_Statics::NewProp_TargetIsCloseRange,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABaseEnemy_Statics::NewProp_CurrentAttackCooldown,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABaseEnemy_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABaseEnemy>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABaseEnemy_Statics::ClassParams = {
		&ABaseEnemy::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ABaseEnemy_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::Class_MetaDataParams), Z_Construct_UClass_ABaseEnemy_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABaseEnemy_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ABaseEnemy()
	{
		if (!Z_Registration_Info_UClass_ABaseEnemy.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABaseEnemy.OuterSingleton, Z_Construct_UClass_ABaseEnemy_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABaseEnemy.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ABaseEnemy>()
	{
		return ABaseEnemy::StaticClass();
	}
	ABaseEnemy::ABaseEnemy() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABaseEnemy);
	ABaseEnemy::~ABaseEnemy() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseEnemy_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseEnemy_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABaseEnemy, ABaseEnemy::StaticClass, TEXT("ABaseEnemy"), &Z_Registration_Info_UClass_ABaseEnemy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABaseEnemy), 3605699768U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseEnemy_h_2588970035(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseEnemy_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseEnemy_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
