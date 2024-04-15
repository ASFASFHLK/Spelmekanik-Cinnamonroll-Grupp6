// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/Enemy_Spawner.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemy_Spawner() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	MYPROJECT_API UClass* Z_Construct_UClass_ABaseEnemy_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_AEnemy_Spawner();
	MYPROJECT_API UClass* Z_Construct_UClass_AEnemy_Spawner_NoRegister();
	MYPROJECT_API UClass* Z_Construct_UClass_ASpawnerGate_NoRegister();
	MYPROJECT_API UScriptStruct* Z_Construct_UScriptStruct_FSpawnLocation();
	UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_SpawnLocation;
class UScriptStruct* FSpawnLocation::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_SpawnLocation.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_SpawnLocation.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSpawnLocation, (UObject*)Z_Construct_UPackage__Script_MyProject(), TEXT("SpawnLocation"));
	}
	return Z_Registration_Info_UScriptStruct_SpawnLocation.OuterSingleton;
}
template<> MYPROJECT_API UScriptStruct* StaticStruct<FSpawnLocation>()
{
	return FSpawnLocation::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FSpawnLocation_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Pos_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Pos;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpawnLocation_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// a bit of a work around as FArrays can not hold FVectors \n" },
#endif
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "a bit of a work around as FArrays can not hold FVectors" },
#endif
	};
#endif
	void* Z_Construct_UScriptStruct_FSpawnLocation_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSpawnLocation>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpawnLocation_Statics::NewProp_Pos_MetaData[] = {
		{ "Category", "Spawn" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSpawnLocation_Statics::NewProp_Pos = { "Pos", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpawnLocation, Pos), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpawnLocation_Statics::NewProp_Pos_MetaData), Z_Construct_UScriptStruct_FSpawnLocation_Statics::NewProp_Pos_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSpawnLocation_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpawnLocation_Statics::NewProp_Pos,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSpawnLocation_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
		nullptr,
		&NewStructOps,
		"SpawnLocation",
		Z_Construct_UScriptStruct_FSpawnLocation_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpawnLocation_Statics::PropPointers),
		sizeof(FSpawnLocation),
		alignof(FSpawnLocation),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpawnLocation_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FSpawnLocation_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpawnLocation_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FSpawnLocation()
	{
		if (!Z_Registration_Info_UScriptStruct_SpawnLocation.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_SpawnLocation.InnerSingleton, Z_Construct_UScriptStruct_FSpawnLocation_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_SpawnLocation.InnerSingleton;
	}
	DEFINE_FUNCTION(AEnemy_Spawner::execOnDeathEvent)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnDeathEvent();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AEnemy_Spawner::execSpawnEnemy)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SpawnEnemy();
		P_NATIVE_END;
	}
	void AEnemy_Spawner::StaticRegisterNativesAEnemy_Spawner()
	{
		UClass* Class = AEnemy_Spawner::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnDeathEvent", &AEnemy_Spawner::execOnDeathEvent },
			{ "SpawnEnemy", &AEnemy_Spawner::execSpawnEnemy },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called when the game starts or when spawned\n" },
#endif
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the game starts or when spawned" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemy_Spawner, nullptr, "OnDeathEvent", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemy_Spawner, nullptr, "SpawnEnemy", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemy_Spawner);
	UClass* Z_Construct_UClass_AEnemy_Spawner_NoRegister()
	{
		return AEnemy_Spawner::StaticClass();
	}
	struct Z_Construct_UClass_AEnemy_Spawner_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_SpawnLocation_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SpawnLocation_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_SpawnLocation;
		static const UECodeGen_Private::FClassPropertyParams NewProp_Enemies_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Enemies_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Enemies;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AmountToSpawnAtStart_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AmountToSpawnAtStart;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnemiesToKill_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_EnemiesToKill;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AmountOfEnemiesSpawned_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AmountOfEnemiesSpawned;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AmountOfEnemiesKilled_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AmountOfEnemiesKilled;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnerGates_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SpawnerGates_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_SpawnerGates;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemy_Spawner_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_AEnemy_Spawner_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AEnemy_Spawner_OnDeathEvent, "OnDeathEvent" }, // 572407097
		{ &Z_Construct_UFunction_AEnemy_Spawner_SpawnEnemy, "SpawnEnemy" }, // 4272555977
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Enemy_Spawner.h" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnLocation_Inner = { "SpawnLocation", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSpawnLocation, METADATA_PARAMS(0, nullptr) }; // 1264402363
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnLocation_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Spawner Settings" },
		{ "MakeEditWidget", "TRUE" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnLocation = { "SpawnLocation", nullptr, (EPropertyFlags)0x0040000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemy_Spawner, SpawnLocation), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnLocation_MetaData), Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnLocation_MetaData) }; // 1264402363
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_Enemies_Inner = { "Enemies", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_ABaseEnemy_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_Enemies_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Spawner Settings" },
		{ "MakeEditWidget", "TRUE" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_Enemies = { "Enemies", nullptr, (EPropertyFlags)0x0044000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemy_Spawner, Enemies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_Enemies_MetaData), Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_Enemies_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountToSpawnAtStart_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Spawner Settings" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountToSpawnAtStart = { "AmountToSpawnAtStart", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemy_Spawner, AmountToSpawnAtStart), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountToSpawnAtStart_MetaData), Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountToSpawnAtStart_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_EnemiesToKill_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Spawner Settings" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_EnemiesToKill = { "EnemiesToKill", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemy_Spawner, EnemiesToKill), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_EnemiesToKill_MetaData), Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_EnemiesToKill_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesSpawned_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Spawner Info" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesSpawned = { "AmountOfEnemiesSpawned", nullptr, (EPropertyFlags)0x0040000000020815, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemy_Spawner, AmountOfEnemiesSpawned), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesSpawned_MetaData), Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesSpawned_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesKilled_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Spawner Info" },
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesKilled = { "AmountOfEnemiesKilled", nullptr, (EPropertyFlags)0x0040000000020815, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemy_Spawner, AmountOfEnemiesKilled), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesKilled_MetaData), Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesKilled_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnerGates_Inner = { "SpawnerGates", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ASpawnerGate_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnerGates_MetaData[] = {
		{ "ModuleRelativePath", "Enemy_Spawner.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnerGates = { "SpawnerGates", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemy_Spawner, SpawnerGates), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnerGates_MetaData), Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnerGates_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemy_Spawner_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnLocation_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_Enemies_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_Enemies,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountToSpawnAtStart,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_EnemiesToKill,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesSpawned,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_AmountOfEnemiesKilled,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnerGates_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemy_Spawner_Statics::NewProp_SpawnerGates,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemy_Spawner_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemy_Spawner>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemy_Spawner_Statics::ClassParams = {
		&AEnemy_Spawner::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AEnemy_Spawner_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemy_Spawner_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemy_Spawner_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AEnemy_Spawner()
	{
		if (!Z_Registration_Info_UClass_AEnemy_Spawner.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemy_Spawner.OuterSingleton, Z_Construct_UClass_AEnemy_Spawner_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AEnemy_Spawner.OuterSingleton;
	}
	template<> MYPROJECT_API UClass* StaticClass<AEnemy_Spawner>()
	{
		return AEnemy_Spawner::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemy_Spawner);
	AEnemy_Spawner::~AEnemy_Spawner() {}
	struct Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_Statics::ScriptStructInfo[] = {
		{ FSpawnLocation::StaticStruct, Z_Construct_UScriptStruct_FSpawnLocation_Statics::NewStructOps, TEXT("SpawnLocation"), &Z_Registration_Info_UScriptStruct_SpawnLocation, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSpawnLocation), 1264402363U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AEnemy_Spawner, AEnemy_Spawner::StaticClass, TEXT("AEnemy_Spawner"), &Z_Registration_Info_UClass_AEnemy_Spawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemy_Spawner), 2969165165U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_1336682380(TEXT("/Script/MyProject"),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_Enemy_Spawner_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
