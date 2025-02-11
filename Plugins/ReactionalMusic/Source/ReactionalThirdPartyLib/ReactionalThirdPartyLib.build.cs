using System;
using System.IO;
using UnrealBuildTool;

public class ReactionalThirdPartyLib : ModuleRules
{
	
	
	private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
    }

	public ReactionalThirdPartyLib(ReadOnlyTargetRules rules) : base(rules)
	{
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
            string PlatformDir = Target.Platform.ToString();
			string BinaryPath = Path.GetFullPath(ModuleDirectory);
            string LibName = "ge_timeline";
            string DLLName = LibName + ".dll";

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, LibName + ".lib"));
            PublicDelayLoadDLLs.Add(DLLName);
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, DLLName));

            //Log.TraceWarningOnce(Path.Combine(ModuleDirectory, LibName + ".lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            string PlatformDir = Target.Platform.ToString();
            string BinaryPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Binaries/ThirdParty", PlatformDir));
            string LibName = "ge_timeline";
            string DylibName = "lib" + LibName + ".dylib";

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib" + LibName + ".dylib"));
            // PublicDelayLoadDLLs.Add(DylibName);
            // RuntimeDependencies.Add(Path.Combine(BinaryPath, DylibName));
            // Note: macOS doesn't use delay-load libraries like Windows, so we don't need to use PublicDelayLoadDLLs
        }
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
            string PlatformDir = Target.Platform.ToString();
            string BinaryPath = Path.GetFullPath(ModuleDirectory);
            string LibName = "libge_timeline";
            string soName = LibName + ".so";

            //Check .xml file transfer of .so files
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, LibName + ".so"));
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, LibName + ".so"));

            //Log.TraceWarningOnce(Path.Combine(ModuleDirectory, LibName + ".lib"));
			
			{
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "libge_timeline_android.xml"));
			}
        }
        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            // Ensure the correct path to the zip file is set
            string EmbeddedFrameworksZipPath = Path.Combine(ModuleDirectory, "iOS", "GE_Timeline.embeddedframework.zip");

            // Add the framework via the embedded zip
            PublicAdditionalFrameworks.Add(new Framework("GE_Timeline", EmbeddedFrameworksZipPath, Framework.FrameworkMode.Copy));
        }
    }
}
