// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class OpenCV_Plugin : ModuleRules
{
	//string OPENCV_VERSION = "460";

	bool LoadOpenCV(ReadOnlyTargetRules Target)
    {
		bool bisLibSupport = false;
		//add  path
		string OpenCVIncludePath = Path.Combine(ModuleDirectory, "../../ThirdParty/OpenCV/includes");
		string OpenCVLibraryPath = Path.Combine(ModuleDirectory, "../../ThirdParty/OpenCV/Libs");

		System.Console.WriteLine("----Architecture -----" + Target.Architecture);

		PublicIncludePaths.AddRange(new string[] { OpenCVIncludePath });

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{

			// Add Library Path 
			//PublicLibraryPaths.Add(OpenCVLibraryPath);

			PublicAdditionalLibraries.Add(Path.Combine(OpenCVLibraryPath, "opencv_world460.lib"));

			//add dynamic library
			PublicDelayLoadDLLs.Add("opencv_ffmpeg460_64.dll");
			PublicDelayLoadDLLs.Add("opencv_world460.dll");
			
			RuntimeDependencies.Add(Path.Combine(OpenCVLibraryPath, "opencv_ffmpeg460_64.dll")); //for package
			RuntimeDependencies.Add(Path.Combine(OpenCVLibraryPath, "opencv_world460.dll"));  //for package

			System.Console.WriteLine("----Library -----" + OpenCVLibraryPath);
			bisLibSupport = true;
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
		}
		else
		{
			string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString());
			System.Console.WriteLine(Err);
		}

		PublicDefinitions.Add(string.Format("WITH_OPENCV={0}", bisLibSupport ? 1 : 0));
		return bisLibSupport;
	}

	public OpenCV_Plugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
				 "RHI",
				"RenderCore"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		LoadOpenCV(Target);
	}
}
