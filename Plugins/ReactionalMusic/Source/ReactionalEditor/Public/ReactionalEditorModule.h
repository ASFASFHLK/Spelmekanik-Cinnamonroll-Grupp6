/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "Modules/ModuleManager.h" // Include to manage the module
#include "ToolMenus.h" // Include for tool menus

class FReactionalEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterMenuExtensions(); // Function to register the button in the toolbar

	void OpenReactionalEditorToolWidget(); 
	void OpenSyncPlatformEditorToolWidget(); 

	TSharedPtr<class FUICommandList> ReactionalPluginCommands;
	
	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray<TSharedPtr<class IAssetTypeActions>> RegisteredAssetTypeActions;
	TArray<FName> CustomPropertyTypeLayouts;
	TArray<FName> CustomClassLayouts;
};