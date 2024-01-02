// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WideMovieActor.generated.h"

UCLASS()
class MYVRPROJECT_API AWideMovieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWideMovieActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UWidgetComponent* movieWidget;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UMediaSource* movieSource;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MySettings")
	class UMediaPlayer* moviePlayer;

	void Back();
	void Stop();
	void Play();
	void Forward();
};
