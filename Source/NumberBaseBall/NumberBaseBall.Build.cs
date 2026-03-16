// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NumberBaseBall : ModuleRules
{
	public NumberBaseBall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
			// Initial Dependencies
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",

        });

        PrivateDependencyModuleNames.AddRange(new string[] { 
             // UI
			"UMG", "Slate", "SlateCore",
        });

        PublicIncludePaths.AddRange(new string[] { 
            "NumberBaseBall",
           
        });
    }
}
