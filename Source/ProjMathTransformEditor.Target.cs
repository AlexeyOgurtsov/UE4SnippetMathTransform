// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjMathTransformEditorTarget : TargetRules
{
	public ProjMathTransformEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "ProjMathTransform" } );
	}
}
