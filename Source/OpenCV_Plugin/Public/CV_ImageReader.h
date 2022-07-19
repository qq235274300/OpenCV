// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#if WITH_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#endif

#include "CV_ImageReader.generated.h"

UCLASS()
class OPENCV_PLUGIN_API ACV_ImageReader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACV_ImageReader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	cv::VideoCapture* stream;
};
