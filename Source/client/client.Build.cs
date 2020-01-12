// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System;
using System.IO;

public class client : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath( Path.Combine( ModulePath, "../ThirdParty/" ) ); }
    }

    public client(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // PublicIncludePathModuleNames.AddRange(new string[] { "Networking" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        
        LoadLibprotobuf(Target);
    }

    public bool LoadLibprotobuf(ReadOnlyTargetRules Target)
    {
        string PlatformString = Target.Platform.ToString();
        string LibrariesPath = Path.Combine(ThirdPartyPath, "libprotobuf", "Libraries");
        // work on linux macos
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, PlatformString, "libprotobuf.lib"));
        }
        else
        {
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, PlatformString, "libprotobuf.a"));
        }

        //if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        //{
        //    isLibrarySupported = true;

        //    string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
        //    string LibrariesPath = Path.Combine(ThirdPartyPath, "BobsMagic", "Libraries");

        //    /*
        //     * test your path with:
        //     * using System; // Console.WriteLine("");
        //     * Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
        //     */

        //    PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "BobsMagic." + PlatformString + ".lib")); 
        //}

        // Include path
        string IncludesPath = Path.Combine( ThirdPartyPath, "libprotobuf", "Includes" ) ;
        PublicIncludePaths.Add( IncludesPath );
        //Console.WriteLine("... IncludePath -> " + IncludesPath );

        //Definitions.Add(string.Format( "WITH_BOBS_MAGIC_BINDING={0}", isLibrarySupported ? 1 : 0 ) );
        // protobuf use no RTTI
        Definitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
        //bUseRTTI = true;

        return true;
    }
}
