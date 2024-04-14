// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HealthComp.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYPROJECT_HealthComp_generated_h
#error "HealthComp.generated.h already included, missing '#pragma once' in HealthComp.h"
#endif
#define MYPROJECT_HealthComp_generated_h

#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_SPARSE_DATA
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetMaxHealth); \
	DECLARE_FUNCTION(execGetHealthPercentage); \
	DECLARE_FUNCTION(execTakeDamage); \
	DECLARE_FUNCTION(execGetCurrentHealth); \
	DECLARE_FUNCTION(execGetMaxHealth); \
	DECLARE_FUNCTION(execSetHealthModifier);


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHealthComp(); \
	friend struct Z_Construct_UClass_UHealthComp_Statics; \
public: \
	DECLARE_CLASS(UHealthComp, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(UHealthComp)


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHealthComp(UHealthComp&&); \
	NO_API UHealthComp(const UHealthComp&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHealthComp); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHealthComp); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHealthComp) \
	NO_API virtual ~UHealthComp();


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_10_PROLOG
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_SPARSE_DATA \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_INCLASS_NO_PURE_DECLS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYPROJECT_API UClass* StaticClass<class UHealthComp>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_HealthComp_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
