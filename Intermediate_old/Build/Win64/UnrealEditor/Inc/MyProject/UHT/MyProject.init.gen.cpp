// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyProject_init() {}
	MYPROJECT_API UFunction* Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature();
	MYPROJECT_API UFunction* Z_Construct_UDelegateFunction_MyProject_OnPickUp__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_MyProject;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_MyProject()
	{
		if (!Z_Registration_Info_UPackage__Script_MyProject.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_MyProject_OnDeath__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_MyProject_OnPickUp__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/MyProject",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xE405F445,
				0x01DE7FCF,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_MyProject.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_MyProject.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_MyProject(Z_Construct_UPackage__Script_MyProject, TEXT("/Script/MyProject"), Z_Registration_Info_UPackage__Script_MyProject, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xE405F445, 0x01DE7FCF));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
