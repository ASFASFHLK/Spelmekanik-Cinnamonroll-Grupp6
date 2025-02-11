using System.IO;
using UnrealBuildTool;

public class ReactionalRuntime : ModuleRules
{
	private string ThirdPartyPath => Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));

	public ReactionalRuntime(ReadOnlyTargetRules rules) : base(rules)
    {
        IWYUSupport = IWYUSupport.None;
        bLegacyPublicIncludePaths = false;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
                "Core",
                "MetasoundEngine",
		        "MetasoundEngineTest",
		        "MetasoundFrontend",
		        "MetasoundGenerator",
                "MetasoundGraphCore",
                "MetasoundStandardNodes"
            }
		);

        PrivateDependencyModuleNames.AddRange(new string[] {
                "CoreUObject",
                "Engine",
                "RenderCore",
                "RHI",
                "NavigationSystem",
                "PhysicsCore",
		        "DeveloperSettings",
		        "AudioMixer",
		        "SignalProcessing",
                "ReactionalThirdPartyLib",
				"Projects",
                "Json",
                "DeveloperSettings",
            }
		);
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[]{ "UnrealEd" });
		}
    }
}