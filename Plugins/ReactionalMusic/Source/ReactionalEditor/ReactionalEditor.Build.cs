using System.IO;
using UnrealBuildTool;

public class ReactionalEditor : ModuleRules
{
    public ReactionalEditor(ReadOnlyTargetRules rules) : base(rules)
    {
        IWYUSupport = IWYUSupport.None;
        bLegacyPublicIncludePaths = false;

#if UE_4_23_OR_LATER
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateIncludePaths.Add("ReactionalEditor/Public");  // Added by Philip for module menu button
#endif

#if UE_4_24_OR_LATER
#else
#endif

        PublicDependencyModuleNames.AddRange(new string[] {
	        "Core",
	        // ... add other public dependencies that you statically link with here ...
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "CoreUObject",
            // ... add private dependencies that you statically link with here ...	
            "Engine",
            "Slate",
            "SlateCore",
            "ToolMenus",
            "RenderCore",
            "RHI",
            "NavigationSystem",
            "UnrealEd",
            "LevelEditor",
            "PropertyEditor",
            "RawMesh",
            "AssetTools",
            "AssetRegistry",
            "Projects",
            "EditorStyle",
            "InputCore",
            "BlueprintGraph",
            "Kismet",
            "GraphEditor",
            "ReactionalRuntime",
            "MetasoundEditor", 
            "Blutility",
            "UMGEditor",
            "UMG",
            "EditorScriptingUtilities",
            
            "UnrealEd",            // Editor functionalities
            "Settings" ,            // Settings registry functionalities
			"SettingsEditor"       // Add this to access ISettingsEditorModule
        });
    }
}