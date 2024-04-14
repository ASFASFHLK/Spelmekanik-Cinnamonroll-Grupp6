// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/ModifierComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeModifierComponent() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseModifier_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_UModifierComponent();
	MYPROJECT_API UClass* Z_Construct_UClass_UModifierComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	DEFINE_FUNCTION(UModifierComponent::execChangeModifiers)
	{
		P_GET_OBJECT(UClass,Z_Param_NewModifier);
		P_GET_PROPERTY(FIntProperty,Z_Param_ModifierPlace);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ChangeModifiers(Z_Param_NewModifier,Z_Param_ModifierPlace);
		P_NATIVE_END;
	}
	void UModifierComponent::StaticRegisterNativesUModifierComponent()
	{
		UClass* Class = UModifierComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ChangeModifiers", &UModifierComponent::execChangeModifiers },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics
	{
		struct ModifierComponent_eventChangeModifiers_Parms
		{
			TSubclassOf<ABaseModifier>  NewModifier;
			int32 ModifierPlace;
		};
		static const UECodeGen_Private::FClassPropertyParams NewProp_NewModifier;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ModifierPlace_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ModifierPlace;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::NewProp_NewModifier = { "NewModifier", nullptr, (EPropertyFlags)0x0014000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ModifierComponent_eventChangeModifiers_Parms, NewModifier), Z_Construct_UClass_UClass, Z_Construct_UClass_ABaseModifier_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::NewProp_ModifierPlace_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::NewProp_ModifierPlace = { "ModifierPlace", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ModifierComponent_eventChangeModifiers_Parms, ModifierPlace), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::NewProp_ModifierPlace_MetaData), Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::NewProp_ModifierPlace_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::NewProp_NewModifier,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::NewProp_ModifierPlace,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ModifierComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UModifierComponent, nullptr, "ChangeModifiers", nullptr, nullptr, Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::PropPointers), sizeof(Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::ModifierComponent_eventChangeModifiers_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::Function_MetaDataParams), Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::ModifierComponent_eventChangeModifiers_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UModifierComponent_ChangeModifiers()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UModifierComponent_ChangeModifiers_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UModifierComponent);
	UClass* Z_Construct_UClass_UModifierComponent_NoRegister()
	{
		return UModifierComponent::StaticClass();
	}
	struct Z_Construct_UClass_UModifierComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ModifierOne_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ModifierOne;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ModifierTwo_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ModifierTwo;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UModifierComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UModifierComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UModifierComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UModifierComponent_ChangeModifiers, "ChangeModifiers" }, // 1830637155
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UModifierComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UModifierComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "ModifierComponent.h" },
		{ "ModuleRelativePath", "ModifierComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierOne_MetaData[] = {
		{ "Category", "ModifierComponent" },
		{ "ModuleRelativePath", "ModifierComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierOne = { "ModifierOne", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UModifierComponent, ModifierOne), Z_Construct_UClass_ABaseModifier_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierOne_MetaData), Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierOne_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierTwo_MetaData[] = {
		{ "Category", "ModifierComponent" },
		{ "ModuleRelativePath", "ModifierComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierTwo = { "ModifierTwo", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UModifierComponent, ModifierTwo), Z_Construct_UClass_ABaseModifier_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierTwo_MetaData), Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierTwo_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UModifierComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierOne,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UModifierComponent_Statics::NewProp_ModifierTwo,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UModifierComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UModifierComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UModifierComponent_Statics::ClassParams = {
		&UModifierComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UModifierComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UModifierComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UModifierComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UModifierComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UModifierComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UModifierComponent()
	{
		if (!Z_Registration_Info_UClass_UModifierComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UModifierComponent.OuterSingleton, Z_Construct_UClass_UModifierComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UModifierComponent.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<UModifierComponent>()
	{
		return UModifierComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UModifierComponent);
	UModifierComponent::~UModifierComponent() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ModifierComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ModifierComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UModifierComponent, UModifierComponent::StaticClass, TEXT("UModifierComponent"), &Z_Registration_Info_UClass_UModifierComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UModifierComponent), 3251169309U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ModifierComponent_h_2261449328(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ModifierComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_ModifierComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
