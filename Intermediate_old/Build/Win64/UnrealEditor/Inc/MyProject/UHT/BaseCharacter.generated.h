// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "BaseCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class AController;
struct FDamageEvent;
#ifdef MYPROJECT_BaseCharacter_generated_h
#error "BaseCharacter.generated.h already included, missing '#pragma once' in BaseCharacter.h"
#endif
#define MYPROJECT_BaseCharacter_generated_h

#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_SPARSE_DATA
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execMoveSidesAxis); \
	DECLARE_FUNCTION(execMoveForwardAxis); \
	DECLARE_FUNCTION(execMoveSides); \
	DECLARE_FUNCTION(execMoveForward); \
	DECLARE_FUNCTION(execTakeDamage);


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_ACCESSORS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_CALLBACK_WRAPPERS
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABaseCharacter(); \
	friend struct Z_Construct_UClass_ABaseCharacter_Statics; \
public: \
	DECLARE_CLASS(ABaseCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(ABaseCharacter)


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABaseCharacter(ABaseCharacter&&); \
	NO_API ABaseCharacter(const ABaseCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABaseCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABaseCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABaseCharacter) \
	NO_API virtual ~ABaseCharacter();


#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_10_PROLOG
#define FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_SPARSE_DATA \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_ACCESSORS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_CALLBACK_WRAPPERS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_INCLASS_NO_PURE_DECLS \
	FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYPROJECT_API UClass* StaticClass<class ABaseCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Spelmekanik_Cinnamonroll_Grupp6_Source_MyProject_BaseCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
