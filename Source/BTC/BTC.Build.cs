// Copyright 2018 Matthias Ring
// Machine Learning and Data Analytics Lab
// Friedrich-Alexander-University Erlangen-Nuremberg
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

using UnrealBuildTool;

public class BTC : ModuleRules
{
	public BTC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { "BTC/Public" });
		PrivateIncludePaths.AddRange(new string[] {	"BTC/Private" });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "InputDevice" });
		PrivateDependencyModuleNames.AddRange( new string[] { "CoreUObject", "Engine", "Slate", "SlateCore", "InputCore" });

		DynamicallyLoadedModuleNames.AddRange(new string[] {});

        // Required for UE >= 4.22
        if (Target.Platform == UnrealTargetPlatform.IOS) {
            PublicFrameworks.AddRange(new string[] { "AVFoundation", "MediaPlayer" });
        }
	}
}
