/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalEditorModule.h"
#include "ToolMenus.h" // Include for working with tool menus
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"
#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "EditorUtilityWidgetBlueprint.h" // Added to support UEditorUtilityWidgetBlueprint
#include "ReactionalEngine.h"
#include "ReactionalBundleDataAssetTypeActions.h"
#include "ReactionalBundleDataAssetDetailsCustomization.h"
#include "EditorUtilitySubsystem.h"
#include "HAL/PlatformProcess.h" // Support Launching URLs
#include "Editor.h"
#include "ISettingsModule.h"
#include "ReactionalEditorStyle.h"
#include "ReactionalSettings.h"


class FToolBarBuilder;
class FMenuBuilder;

#define LOCTEXT_NAMESPACE "FReactionalEditorModule"

IMPLEMENT_MODULE(FReactionalEditorModule, ReactionalEditor)
#pragma optimize("", off)
void FReactionalEditorModule::StartupModule()
{
	// Register Reactional Icon Style
	FReactionalEditorStyle::Initialize();

	// Register the function to be called when the menu system is initialized
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FReactionalEditorModule::RegisterMenuExtensions));

	RegisteredAssetTypeActions.Reset();
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	TSharedRef<IAssetTypeActions> AssetTypeAction = MakeShareable(new FAssetTypeActions_ReactionalBundleDataAsset());
	AssetTools.RegisterAssetTypeActions(AssetTypeAction);
	RegisteredAssetTypeActions.Add(AssetTypeAction);

	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	CustomPropertyTypeLayouts.Reset();
	CustomPropertyTypeLayouts.Add(FReactionalBundle::StaticStruct()->GetFName());
	PropertyModule.RegisterCustomPropertyTypeLayout(
		CustomPropertyTypeLayouts.Last(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FReactionalBundlePropertyTypeCustomization::MakeInstance)
	);

	CustomClassLayouts.Reset();
	CustomClassLayouts.Add(UReactionalBundleDataAsset::StaticClass()->GetFName());
	PropertyModule.RegisterCustomClassLayout(
		CustomClassLayouts.Last(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FReactionalBundleDetailCustomization::MakeInstance)
	);
}

void FReactionalEditorModule::ShutdownModule()
{
	// Unregister Reactional Icon Style 
	FReactionalEditorStyle::Shutdown();

	// Unregister the startup callback
	UToolMenus::UnRegisterStartupCallback(this);

	// Unregister any menu extensions owned by this module
	UToolMenus::UnregisterOwner(this);

	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (AssetToolsModule)
	{
		for (int i = 0; i < RegisteredAssetTypeActions.Num(); i++)
		{
			AssetToolsModule->Get().UnregisterAssetTypeActions(RegisteredAssetTypeActions[i].ToSharedRef());
		}
	}

	FPropertyEditorModule* PropertyEditorModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor");
	if (PropertyEditorModule)
	{
		for (FName CustomPropertyTypeLayout : CustomPropertyTypeLayouts)
		{
			PropertyEditorModule->UnregisterCustomPropertyTypeLayout(CustomPropertyTypeLayout);
		}
		for (FName CustomClassLayout : CustomClassLayouts)
		{
			PropertyEditorModule->UnregisterCustomClassLayout(CustomClassLayout);
		}
	}
}

/***
 *Reactional Editor Widget 
 *Handeling Testing of Bundles in Editor and Runtime
 */
void FReactionalEditorModule::OpenReactionalEditorToolWidget()
{
	// Load the widget blueprint by its asset path
	UEditorUtilityWidgetBlueprint* WidgetBlueprint = LoadObject<UEditorUtilityWidgetBlueprint>(
	nullptr, TEXT("/ReactionalMusic/EditorTool/WBP_Reactional_EditorTool.WBP_Reactional_EditorTool"));

	if (WidgetBlueprint)
	{
		UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		if (EditorUtilitySubsystem)
		{
			// Open widget with EditorUtilitySubsystem
			EditorUtilitySubsystem->SpawnAndRegisterTab(WidgetBlueprint);
			UE_LOG(LogTemp, Warning, TEXT("Reactional Music Editor Tool Opened"));
		}
		else UE_LOG(LogTemp, Error, TEXT("Failed to get EditorUtilitySubsystem"));
	}
	else UE_LOG(LogTemp, Error, TEXT("Widget blueprint not found"));
}

/***
 *Platform Editor Widget 
 *Handeling Synced Login to Platform and Set Active Synced Bundle
 */
void FReactionalEditorModule::OpenSyncPlatformEditorToolWidget()
{
	// Load the widget blueprint by its asset path
	UEditorUtilityWidgetBlueprint* PlatformWidgetBlueprint = LoadObject<UEditorUtilityWidgetBlueprint>(
	nullptr, TEXT("/ReactionalMusic/EditorTool/WBP_Reactional_SyncToPlatform_EditorTool.WBP_Reactional_SyncToPlatform_EditorTool"));

	if (PlatformWidgetBlueprint)
	{
		UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		if (EditorUtilitySubsystem)
		{
			// Open widget with EditorUtilitySubsystem
			EditorUtilitySubsystem->SpawnAndRegisterTab(PlatformWidgetBlueprint);
			UE_LOG(LogTemp, Warning, TEXT("Reactional Sync Platform Tool Opened"));
		}
		else UE_LOG(LogTemp, Error, TEXT("Failed to get EditorUtilitySubsystem"));
	}
	else UE_LOG(LogTemp, Error, TEXT("Widget blueprint not found"));
}


/**
  Modified the RegisterMenuExtensions function to create a custom Reactional Menu
 */
void FReactionalEditorModule::RegisterMenuExtensions()
{
	// Extend the "Tools" menu in the Level Editor's main menu.
	UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");

	// Create a new section under "Tools" for the Reactional items.
	FToolMenuSection& ReactionalMusicSection = ToolsMenu->AddSection(
		"ReactionalSection",
		INVTEXT("Reactional Music"),
		FToolMenuInsert(TEXT("Instrumentation"), EToolMenuInsertType::Before)
	);
	
	// Add a "Reactional" submenu to the "Tools" menu.
	ReactionalMusicSection.AddSubMenu(
		"ReactionalSubMenu", // Unique name for internal use.
		INVTEXT("Reactional"), // Display name for the submenu.
		INVTEXT("Explore the Reactional Options"), // Tooltip for the submenu.
		
		FNewToolMenuDelegate::CreateLambda([this](UToolMenu* ReactionalSubMenu)
		{
			// Add section to visually separate the entries.
			FToolMenuSection& ReactionalSection = ReactionalSubMenu->AddSection(
				"ReactionalSection",
				INVTEXT("Reactional")
			);

			// Add separate platform entry until submenu (commented out bellow) will be in use
			ReactionalSection.AddMenuEntry(
				"PlatformEntry",
				INVTEXT("Visit Platform"),
				INVTEXT("Go to the Reactional Web Platform"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					FString ErrorMsg;
					const FString URL = TEXT("https://app.reactionalmusic.com/start");
					FPlatformProcess::LaunchURL(*URL, nullptr, &ErrorMsg);

					if (!ErrorMsg.IsEmpty())
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to launch URL: %s - Error: %s"), *URL, *ErrorMsg);
					}
					else
					{
						UE_LOG(LogTemp, Log, TEXT("Welcome to Reactional Platform"));
					}
				}))
			);
			//// Add a nested submenu for the platform.
			//ReactionalSection.AddSubMenu(
			//	"PlatformSubMenu", // Unique name for internal use.
			//	INVTEXT("Platform"), // Display name for the submenu.
			//	INVTEXT("Platform Specific Options"), // Tooltip for the submenu.
			//	FNewToolMenuDelegate::CreateLambda([](UToolMenu* PlatformSubMenu)
			//	{
			//		// Add section to visually separate the entries.
			//		FToolMenuSection& PlatformSection = PlatformSubMenu->AddSection(
			//			"PlatformSection", INVTEXT("Platform"));

			//		// Adding "Developer Sync Platform" Entry
			//		//PlatformSection.AddMenuEntry(
			//		//	"DevSyncPlatformEntry",
			//		//	INVTEXT("Developer Sync Platform"),
			//		//	INVTEXT("Login as Developer and Sync your Bundles to the Platform Live in Unreal"),
			//		//	FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
			//		//	FUIAction(FExecuteAction::CreateLambda([]
			//		//	{
			//		//		UE_LOG(LogTemp, Log, TEXT("Launching the Sync to Platform..."));

			//		//		if (FReactionalEditorModule* ReactionalModule = FModuleManager::GetModulePtr<
			//		//			FReactionalEditorModule>("ReactionalEditor"))
			//		//		{
			//		//			// Call the function to open the widget
			//		//			ReactionalModule->OpenSyncPlatformEditorToolWidget();
			//		//		}
			//		//		else
			//		//		{
			//		//			UE_LOG(LogTemp, Error, TEXT("Failed to Open Developer Login Widget"));
			//		//		}
			//		//}))
			//		//);

			//		// Adding "Platform" Entry
			//		PlatformSection.AddMenuEntry(
			//			"PlatformEntry",
			//			INVTEXT("Visit Platform"),
			//			INVTEXT("Click to Visit The Platform on Web"),
			//			FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
			//			FUIAction(FExecuteAction::CreateLambda([]
			//			{
			//				FString ErrorMsg;
			//				const FString URL = TEXT("https://app.reactionalmusic.com/start");
			//				FPlatformProcess::LaunchURL(*URL, nullptr, &ErrorMsg);

			//				if (!ErrorMsg.IsEmpty())
			//				{
			//					UE_LOG(LogTemp, Error, TEXT("Failed to launch URL: %s - Error: %s"), *URL, *ErrorMsg);
			//				}
			//				else
			//				{
			//					UE_LOG(LogTemp, Log, TEXT("Welcome to Reactional Platform"));
			//				}
			//			}))
			//		);
			//	})
			//);

			// Adding "Docs" Entry
			ReactionalSection.AddMenuEntry(
				"DocumentationEntry",
				INVTEXT("Documentation"),
				INVTEXT("Go to the Reactional Unreal API Documentation website"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					FString ErrorMsg;
					const FString URL = TEXT("https://docs.reactionalmusic.com/Unreal/");
					FPlatformProcess::LaunchURL(*URL, nullptr, &ErrorMsg);

					if (!ErrorMsg.IsEmpty())
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to launch URL: %s - Error: %s"), *URL, *ErrorMsg);
					}
					else
					{
						UE_LOG(LogTemp, Log, TEXT("Welcome to Reactional Docs"));
					}
				}))
			);

			// Adding "Discord" Entry
			ReactionalSection.AddMenuEntry(
				"DiscordEntry",
				INVTEXT("Discord Community"),
				INVTEXT("Show off work or connect with the Reactional Community, Head over to Discord"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					FString ErrorMsg;
					const FString URL = TEXT("https://discord.gg/bAJNRdXq4c");
					FPlatformProcess::LaunchURL(*URL, nullptr, &ErrorMsg);

					if (!ErrorMsg.IsEmpty())
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to launch URL: %s - Error: %s"), *URL, *ErrorMsg);
					}
					else
					{
						UE_LOG(LogTemp, Log, TEXT("Welcome to Reactional Discord"));
					}
				}))
			);

			// Adding "Support" Entry
			ReactionalSection.AddMenuEntry(
				"ForumEntry",
				INVTEXT("Forum Support"),
				INVTEXT("If you encounter a issue with the plugin, report it in the forum"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					FString ErrorMsg;
					const FString URL = TEXT("https://forum.reactionalmusic.com/");
					FPlatformProcess::LaunchURL(*URL, nullptr, &ErrorMsg);

					if (!ErrorMsg.IsEmpty())
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to launch URL: %s - Error: %s"), *URL, *ErrorMsg);
					}
					else UE_LOG(LogTemp, Log, TEXT("Welcome to Reactional Forum"));
				}))
			);
			
			// Adding "Web App" Entry
			ReactionalSection.AddMenuEntry(
				"ReactionalEntry",
				INVTEXT("Reactional Website"),
				INVTEXT("Reactional Music Website"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					FString ErrorMsg;
					const FString URL = TEXT("https://reactionalmusic.com/");
					FPlatformProcess::LaunchURL(*URL, nullptr, &ErrorMsg);

					if (!ErrorMsg.IsEmpty())
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to launch URL: %s - Error: %s"), *URL, *ErrorMsg);
					}
					else UE_LOG(LogTemp, Log, TEXT("Welcome to Reactional Music"));
				}))
			);

			// Add section to visually separate the entrys.
			FToolMenuSection& UnrealSection = ReactionalSubMenu->AddSection(
				"ReactionalUnrealSection",
				INVTEXT("Editor")
			);

			// Adding "Open Reactional Settings" Entry
			UnrealSection.AddMenuEntry(
				"ReactionalSettingsEntry",
				INVTEXT("Plugin Project Settings"),
				INVTEXT("Open Project Settings/Reactional to set Reactional Specific settings for your project"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					UE_LOG(LogTemp, Log, TEXT("Add Reactional Settings Entry Clicked!"));

					// Load the Settings module and open the specific settings page
					if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
					{
						UReactionalSettings* ReactionalMusicSettings = GetMutableDefault<UReactionalSettings>();
						// Use ShowViewer to directly navigate to the specific section
						SettingsModule->ShowViewer(
							ReactionalMusicSettings->GetContainerName(),
							ReactionalMusicSettings->GetCategoryName(),
							ReactionalMusicSettings->GetSectionName()
						);
					}
					else UE_LOG(LogTemp, Error, TEXT("Failed to load Settings module."));
				}))
			);


			UnrealSection.AddMenuEntry(
				"ReactionalWidgetEntry",
				INVTEXT("Reactional Editor Widget"),
				INVTEXT("Click To Open Reactional Editor Widget And Test Your Theme"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateRaw(this, &FReactionalEditorModule::OpenReactionalEditorToolWidget))
			);

			// Add a nested submenu for the platform.
			//UnrealSection.AddSubMenu(
			//	"DeepAnalysisSubMenu", // Unique name for internal use.
			//	INVTEXT("Deep Analysis"), // Display name for the submenu.
			//	INVTEXT("Deep Analysis options for your bundle"), // Tooltip for the submenu.
			//	FNewToolMenuDelegate::CreateLambda([](UToolMenu* DeepAnalysisSubMenu)
			//	{
			//		// Add section to visually separate the entries.
			//		FToolMenuSection& DeepAnalysisSection = DeepAnalysisSubMenu->AddSection(
			//			"DeepAnalysisSection", INVTEXT("Deep Analysis"));

			//		DeepAnalysisSection.AddMenuEntry(
			//			"DumpMusicEntry",
			//			INVTEXT("Dump Music Data Asset"),
			//			INVTEXT("Create your Deep Analysis Data Asset"),
			//			FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
			//			FUIAction(FExecuteAction::CreateLambda([]
			//			{
			//				UE_LOG(LogTemp, Log, TEXT("Cooming soon: Creating your Deep Analysis Data Asset"));
			//			}))
			//		);
			//	})
			//);
			//TODO Change to use FHttpModule to make Get Request and enable download path and unzip in Unreal 

			// Add a nested submenu for the platform.
			UnrealSection.AddSubMenu(
				"DownloadGameSubMenu",
				INVTEXT("Download Games"),
				INVTEXT("Download one of our Reactional Demo Templets"),
				FNewToolMenuDelegate::CreateLambda([](UToolMenu* DownloadGamesSubMenu)
				{
					// Add section to visually separate the entries.
					FToolMenuSection& ReactionalGameTempletSection = DownloadGamesSubMenu->AddSection(
						"DeepAnalysisSection",
						INVTEXT("Reactional Game Templets")
					);


					ReactionalGameTempletSection.AddMenuEntry(
						"DownloadDemoSceneEntry",
						INVTEXT("Reactional Demo Scene"),
						INVTEXT("Get the Interactive Demo Scene"),
						FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
						FUIAction(FExecuteAction::CreateLambda([]
						{
							UE_LOG(LogTemp, Log, TEXT("Download Reactional Templet..."));

							FString ErrorMsg;
							const FString URL = TEXT(
								"https://cdn.reactionalmusic.com/demo-scenes/unreal/ReactionalUnrealDemo.zip?Expires=1732311534&KeyName=cdn-signing-key-may23&Signature=uiRwhTIvDnJBT4y8tH45OpXPeI0");
							FPlatformProcess::LaunchURL(*URL, nullptr, &ErrorMsg);

							if (!ErrorMsg.IsEmpty())
							{
								UE_LOG(LogTemp, Error, TEXT("Failed to Download Reactional Templet: %s - Error: %s"),
								       *URL, *ErrorMsg);
							}
							else UE_LOG(LogTemp, Log, TEXT("Download Complete"));
						}))
					);
				})
			);

			// Add section to visually separate the entrys.
			FToolMenuSection& MiscSection = ReactionalSubMenu->AddSection("ReactionalMiscSection",INVTEXT("Misc"));

			// Adding "Readme" Entry
			MiscSection.AddMenuEntry(
				"ReadmeEntry",
				INVTEXT("Readme"),
				INVTEXT("Open README.md"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					FString FilePath = FPaths::ConvertRelativePathToFull(
						FPaths::ProjectPluginsDir() + TEXT("ReactionalMusic/README.md"));

					if (FPlatformProcess::LaunchFileInDefaultExternalApplication(*FilePath))
					{
						UE_LOG(LogTemp, Log, TEXT("Opened README.md: %s"), *FilePath);
					}
					else UE_LOG(LogTemp, Error, TEXT("Failed to open README.md: %s"), *FilePath);
				}))
			);

			// Adding "Changelog" Entry
			MiscSection.AddMenuEntry(
				"ChangelogEntry",
				INVTEXT("Changelog"),
				INVTEXT("Open CHANGELOG.md"),
				FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon"),
				FUIAction(FExecuteAction::CreateLambda([]
				{
					FString FilePath = FPaths::ConvertRelativePathToFull(
						FPaths::ProjectPluginsDir() + TEXT("ReactionalMusic/CHANGELOG.md"));

					if (FPlatformProcess::LaunchFileInDefaultExternalApplication(*FilePath))
					{
						UE_LOG(LogTemp, Log, TEXT("Opened CHANGELOG.md: %s"), *FilePath);
					}
					else UE_LOG(LogTemp, Error, TEXT("Failed to open CHANGELOG.md: %s"), *FilePath);
				}))
			);
		})
	);

	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.ModesToolBar");
	FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("File");

	// Modify button to open the widget on click
	ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(
		TEXT("ReactionalWidget"),
		FExecuteAction::CreateRaw(this, &FReactionalEditorModule::OpenReactionalEditorToolWidget),
		// Updated action to call OpenReactionalEditorTool
		INVTEXT("ReactionalEditorButton"),
		INVTEXT("Click To Open Reactional Editor Widget And Test Your Theme"),
		FSlateIcon(FReactionalEditorStyle::GetStyleSetName(), "ReactionalWidget.Icon")
	));
}

#pragma optimize("", on)
#undef LOCTEXT_NAMESPACE