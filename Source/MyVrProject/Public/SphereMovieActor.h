// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereMovieActor.generated.h"

UCLASS()
class MYVRPROJECT_API ASphereMovieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASphereMovieActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Components")
	class UMediaSoundComponent* soundComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Variables")
	class UMediaPlayer* mediaPlayer;

	UPROPERTY(EditAnywhere, Category="MySettings|Variables")
	class UMediaSource* mediaSource;
};
