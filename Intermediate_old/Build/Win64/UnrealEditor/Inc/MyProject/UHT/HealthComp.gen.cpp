// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/HealthComp.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHealthComp() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	MYPROJECT_API UClass* Z_Construct_UClass_UHealthComp();
	MYPROJECT_API UClass* Z_Construct_UClass_UHealthComp_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	DEFINE_FUNCTION(UHealthComp::execSetMaxHealth)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_NewMaxHealthValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetMaxHealth(Z_Param_NewMaxHealthValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHealthComp::execGetHealthPercentage)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->GetHealthPercentage();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHealthComp::execTakeDamage)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_DamageToTake);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->TakeDamage(Z_Param_DamageToTake);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHealthComp::execGetCurrentHealth)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetCurrentHealth();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHealthComp::execGetMaxHealth)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetMaxHealth();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHealthComp::execSetHealthModifier)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_NewHealthModifier);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetHealthModifier(Z_Param_NewHealthModifier);
		P_NATIVE_END;
	}
	void UHealthComp::StaticRegisterNativesUHealthComp()
	{
		UClass* Class = UHealthComp::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetCurrentHealth", &UHealthComp::execGetCurrentHealth },
			{ "GetHealthPercentage", &UHealthComp::execGetHealthPercentage },
			{ "GetMaxHealth", &UHealthComp::execGetMaxHealth },
			{ "SetHealthModifier", &UHealthComp::execSetHealthModifier },
			{ "SetMaxHealth", &UHealthComp::execSetMaxHealth },
			{ "TakeDamage", &UHealthComp::execTakeDamage },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics
	{
		struct HealthComp_eventGetCurrentHealth_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComp_eventGetCurrentHealth_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthComp, nullptr, "GetCurrentHealth", nullptr, nullptr, Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::HealthComp_eventGetCurrentHealth_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::HealthComp_eventGetCurrentHealth_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UHealthComp_GetCurrentHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComp_GetCurrentHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics
	{
		struct HealthComp_eventGetHealthPercentage_Parms
		{
			float ReturnValue;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComp_eventGetHealthPercentage_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthComp, nullptr, "GetHealthPercentage", nullptr, nullptr, Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::HealthComp_eventGetHealthPercentage_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::HealthComp_eventGetHealthPercentage_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UHealthComp_GetHealthPercentage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComp_GetHealthPercentage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics
	{
		struct HealthComp_eventGetMaxHealth_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComp_eventGetMaxHealth_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthComp, nullptr, "GetMaxHealth", nullptr, nullptr, Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::HealthComp_eventGetMaxHealth_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::HealthComp_eventGetMaxHealth_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UHealthComp_GetMaxHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComp_GetMaxHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics
	{
		struct HealthComp_eventSetHealthModifier_Parms
		{
			int32 NewHealthModifier;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewHealthModifier;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::NewProp_NewHealthModifier = { "NewHealthModifier", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComp_eventSetHealthModifier_Parms, NewHealthModifier), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::NewProp_NewHealthModifier,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthComp, nullptr, "SetHealthModifier", nullptr, nullptr, Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::HealthComp_eventSetHealthModifier_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::HealthComp_eventSetHealthModifier_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UHealthComp_SetHealthModifier()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComp_SetHealthModifier_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics
	{
		struct HealthComp_eventSetMaxHealth_Parms
		{
			int32 NewMaxHealthValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewMaxHealthValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::NewProp_NewMaxHealthValue = { "NewMaxHealthValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComp_eventSetMaxHealth_Parms, NewMaxHealthValue), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::NewProp_NewMaxHealthValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthComp, nullptr, "SetMaxHealth", nullptr, nullptr, Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::HealthComp_eventSetMaxHealth_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::HealthComp_eventSetMaxHealth_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UHealthComp_SetMaxHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComp_SetMaxHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHealthComp_TakeDamage_Statics
	{
		struct HealthComp_eventTakeDamage_Parms
		{
			int32 DamageToTake;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_DamageToTake;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::NewProp_DamageToTake = { "DamageToTake", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HealthComp_eventTakeDamage_Parms, DamageToTake), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((HealthComp_eventTakeDamage_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(HealthComp_eventTakeDamage_Parms), &Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::NewProp_DamageToTake,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHealthComp, nullptr, "TakeDamage", nullptr, nullptr, Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::HealthComp_eventTakeDamage_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::HealthComp_eventTakeDamage_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UHealthComp_TakeDamage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHealthComp_TakeDamage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHealthComp);
	UClass* Z_Construct_UClass_UHealthComp_NoRegister()
	{
		return UHealthComp::StaticClass();
	}
	struct Z_Construct_UClass_UHealthComp_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxHealth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HealthModifier_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_HealthModifier;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHealthComp_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComp_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UHealthComp_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UHealthComp_GetCurrentHealth, "GetCurrentHealth" }, // 1007436446
		{ &Z_Construct_UFunction_UHealthComp_GetHealthPercentage, "GetHealthPercentage" }, // 205904896
		{ &Z_Construct_UFunction_UHealthComp_GetMaxHealth, "GetMaxHealth" }, // 2918558760
		{ &Z_Construct_UFunction_UHealthComp_SetHealthModifier, "SetHealthModifier" }, // 2762912473
		{ &Z_Construct_UFunction_UHealthComp_SetMaxHealth, "SetMaxHealth" }, // 1754991055
		{ &Z_Construct_UFunction_UHealthComp_TakeDamage, "TakeDamage" }, // 3877804519
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComp_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHealthComp_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "HealthComp.h" },
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHealthComp_Statics::NewProp_MaxHealth_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "HealthComp" },
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthComp_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0040000000010005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComp, MaxHealth), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComp_Statics::NewProp_MaxHealth_MetaData), Z_Construct_UClass_UHealthComp_Statics::NewProp_MaxHealth_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHealthComp_Statics::NewProp_HealthModifier_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "HealthComp" },
		{ "ModuleRelativePath", "HealthComp.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UHealthComp_Statics::NewProp_HealthModifier = { "HealthModifier", nullptr, (EPropertyFlags)0x0040000000000805, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthComp, HealthModifier), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComp_Statics::NewProp_HealthModifier_MetaData), Z_Construct_UClass_UHealthComp_Statics::NewProp_HealthModifier_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHealthComp_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComp_Statics::NewProp_MaxHealth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthComp_Statics::NewProp_HealthModifier,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHealthComp_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHealthComp>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UHealthComp_Statics::ClassParams = {
		&UHealthComp::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UHealthComp_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComp_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComp_Statics::Class_MetaDataParams), Z_Construct_UClass_UHealthComp_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthComp_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UHealthComp()
	{
		if (!Z_Registration_Info_UClass_UHealthComp.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHealthComp.OuterSingleton, Z_Construct_UClass_UHealthComp_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UHealthComp.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<UHealthComp>()
	{
		return UHealthComp::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHealthComp);
	UHealthComp::~UHealthComp() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UHealthComp, UHealthComp::StaticClass, TEXT("UHealthComp"), &Z_Registration_Info_UClass_UHealthComp, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHealthComp), 3529520403U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_1608775338(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
