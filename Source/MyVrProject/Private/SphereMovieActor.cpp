// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereMovieActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MediaSoundComponent.h"
#include "MediaSource.h"
#include "MediaPlayer.h"


ASphereMovieActor::ASphereMovieActor()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);
	rootComp->SetWorldScale3D(FVector(3.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	soundComp = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Sound Comp"));
	soundComp->SetupAttachment(RootComponent);

	if (mediaPlayer != nullptr)
	{
		soundComp->SetMediaPlayer(mediaPlayer);
	}
}

void ASphereMovieActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (mediaPlayer != nullptr && mediaSource != nullptr)
	{
		mediaPlayer->OpenSource(mediaSource);
		//soundComp->Activate(true);
		//soundComp->SetVolumeMultiplier(1.0f);
	}
}

void ASphereMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

