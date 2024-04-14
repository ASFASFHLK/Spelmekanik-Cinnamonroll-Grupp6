// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PlayerCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYPROJECT_PlayerCharacter_generated_h
#error "PlayerCharacter.generated.h already included, missing '#pragma once' in PlayerCharacter.h"
#endif
#define MYPROJECT_PlayerCharacter_generated_h

#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_SPARSE_DATA
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execShoot); \
	DECLARE_FUNCTION(execLookSides); \
	DECLARE_FUNCTION(execLookUp); \
	DECLARE_FUNCTION(execFire);


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPlayerCharacter(); \
	friend struct Z_Construct_UClass_APlayerCharacter_Statics; \
public: \
	DECLARE_CLASS(APlayerCharacter, ABaseCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(APlayerCharacter)


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APlayerCharacter(APlayerCharacter&&); \
	NO_API APlayerCharacter(const APlayerCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APlayerCharacter) \
	NO_API virtual ~APlayerCharacter();


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_17_PROLOG
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_SPARSE_DATA \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_INCLASS_NO_PURE_DECLS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYPROJECT_API UClass* StaticClass<class APlayerCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_PlayerCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
