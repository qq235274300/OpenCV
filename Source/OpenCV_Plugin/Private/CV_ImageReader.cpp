// Fill out your copyright notice in the Description page of Project Settings.


#include "CV_ImageReader.h"
#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include  <stdio.h>
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"

#if PLATFORM_WINDOWS
#include  <direct.h>
#endif


#include <string>
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFilemanager.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"	
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;

// Sets default values
ACV_ImageReader::ACV_ImageReader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACV_ImageReader::BeginPlay()
{
	Super::BeginPlay();

#if PLATFORM_WINDOWS
	FString ContentPath = FPaths::ProjectContentDir();
	FString TestImgPath = FPaths::Combine(ContentPath, TEXT("TestRes/test.png"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*TestImgPath))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("TestImgPath == %s not exist "), *TestImgPath));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("TestImgPath == %s exist "), *TestImgPath));
	}


	std::string temp(TCHAR_TO_UTF8(*TestImgPath));

	Mat img = imread(temp, IMREAD_UNCHANGED);
	if (img.empty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Opencv open img failed!"));
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Opencv open img Success!"));
	}
	//Write Img
	FString ts = ContentPath + "TestRes/ttwin.jpeg";
	imwrite(TCHAR_TO_UTF8(*ts), img);

	namedWindow("Example", WINDOW_AUTOSIZE);
	imshow("Example", img);


	//Mat img = imread(temp, IMREAD_UNCHANGED);
	//if (img.empty())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Opencv open img failed!"));
	//	return;
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Opencv open img Success!"));
	//}
	////Write Img
	//FString ts = ContentPath + "TestRes/ttwin.jpeg";
	//imwrite(TCHAR_TO_UTF8(*ts), img);

	//namedWindow("Example", WINDOW_AUTOSIZE);
	//imshow("Example", img);

#endif
	
}

// Called every frame
void ACV_ImageReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

