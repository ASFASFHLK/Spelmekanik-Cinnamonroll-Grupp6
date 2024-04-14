// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/DefaultGamemode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDefaultGamemode() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	MYPROJECT_API UClass* Z_Construct_UClass_ADefaultGamemode();
	MYPROJECT_API UClass* Z_Construct_UClass_ADefaultGamemode_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	DEFINE_FUNCTION(ADefaultGamemode::execEndGame)
	{
		P_GET_UBOOL(Z_Param_PlayerWin);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EndGame(Z_Param_PlayerWin);
		P_NATIVE_END;
	}
	void ADefaultGamemode::StaticRegisterNativesADefaultGamemode()
	{
		UClass* Class = ADefaultGamemode::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EndGame", &ADefaultGamemode::execEndGame },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics
	{
		struct DefaultGamemode_eventEndGame_Parms
		{
			bool PlayerWin;
		};
		static void NewProp_PlayerWin_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_PlayerWin;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::NewProp_PlayerWin_SetBit(void* Obj)
	{
		((DefaultGamemode_eventEndGame_Parms*)Obj)->PlayerWin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::NewProp_PlayerWin = { "PlayerWin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(DefaultGamemode_eventEndGame_Parms), &Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::NewProp_PlayerWin_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::NewProp_PlayerWin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "DefaultGamemode.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADefaultGamemode, nullptr, "EndGame", nullptr, nullptr, Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::PropPointers), sizeof(Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::DefaultGamemode_eventEndGame_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::Function_MetaDataParams), Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::DefaultGamemode_eventEndGame_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ADefaultGamemode_EndGame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ADefaultGamemode_EndGame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ADefaultGamemode);
	UClass* Z_Construct_UClass_ADefaultGamemode_NoRegister()
	{
		return ADefaultGamemode::StaticClass();
	}
	struct Z_Construct_UClass_ADefaultGamemode_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WinScreen_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_WinScreen;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LoseScreen_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_LoseScreen;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADefaultGamemode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADefaultGamemode_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ADefaultGamemode_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADefaultGamemode_EndGame, "EndGame" }, // 2309338373
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADefaultGamemode_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADefaultGamemode_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "DefaultGamemode.h" },
		{ "ModuleRelativePath", "DefaultGamemode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_WinScreen_MetaData[] = {
		{ "Category", "DefaultGamemode" },
		{ "ModuleRelativePath", "DefaultGamemode.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_WinScreen = { "WinScreen", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADefaultGamemode, WinScreen), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_WinScreen_MetaData), Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_WinScreen_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_LoseScreen_MetaData[] = {
		{ "Category", "DefaultGamemode" },
		{ "ModuleRelativePath", "DefaultGamemode.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_LoseScreen = { "LoseScreen", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ADefaultGamemode, LoseScreen), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_LoseScreen_MetaData), Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_LoseScreen_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADefaultGamemode_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_WinScreen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADefaultGamemode_Statics::NewProp_LoseScreen,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADefaultGamemode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADefaultGamemode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ADefaultGamemode_Statics::ClassParams = {
		&ADefaultGamemode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADefaultGamemode_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADefaultGamemode_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ADefaultGamemode_Statics::Class_MetaDataParams), Z_Construct_UClass_ADefaultGamemode_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ADefaultGamemode_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ADefaultGamemode()
	{
		if (!Z_Registration_Info_UClass_ADefaultGamemode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADefaultGamemode.OuterSingleton, Z_Construct_UClass_ADefaultGamemode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ADefaultGamemode.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<ADefaultGamemode>()
	{
		return ADefaultGamemode::StaticClass();
	}
	ADefaultGamemode::ADefaultGamemode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADefaultGamemode);
	ADefaultGamemode::~ADefaultGamemode() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DefaultGamemode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DefaultGamemode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ADefaultGamemode, ADefaultGamemode::StaticClass, TEXT("ADefaultGamemode"), &Z_Registration_Info_UClass_ADefaultGamemode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADefaultGamemode), 526859592U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DefaultGamemode_h_4111524520(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DefaultGamemode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_DefaultGamemode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
