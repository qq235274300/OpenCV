// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenCV_Plugin.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FOpenCV_PluginModule"

void FOpenCV_PluginModule::StartupModule()
{
	const FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("OpenCV_Plugin"))->GetBaseDir();
	FString LibraryPath;

//#if PLATFORM_WINDOWS
#if WITH_OPENCV
	LibraryPath = FPaths::Combine(*PluginDir, TEXT("ThirdParty/OpenCV/Libs/"));
	UE_LOG(LogTemp, Warning, TEXT("opencv world LibraryPath == %s"), *(LibraryPath + TEXT("opencv_world460.dll")));
	OpenCV_World_Handler = FPlatformProcess::GetDllHandle(*(LibraryPath + TEXT("opencv_world460.dll")));
	OpenCV_FFmpeg_Handler = FPlatformProcess::GetDllHandle(*(LibraryPath + TEXT("opencv_ffmpeg460_64.dll")));
	if (!OpenCV_World_Handler || !OpenCV_FFmpeg_Handler)
	{
		UE_LOG(LogTemp, Error, TEXT("Load OpenCV dll failed!"));
	}
#endif
}

void FOpenCV_PluginModule::ShutdownModule()
{
#if WITH_OPENCV
	if (OpenCV_World_Handler)
	{
		FPlatformProcess::FreeDllHandle(OpenCV_World_Handler);
		OpenCV_World_Handler = nullptr;
	}
	if (OpenCV_FFmpeg_Handler)
	{
		FPlatformProcess::FreeDllHandle(OpenCV_FFmpeg_Handler);
		OpenCV_FFmpeg_Handler = nullptr;
	}	
#elif PLATFORM_ANDROID

#elif PLATFORM_IOS

#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOpenCV_PluginModule, OpenCV_Plugin)