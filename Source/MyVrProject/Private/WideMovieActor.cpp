// Fill out your copyright notice in the Description page of Project Settings.


#include "WideMovieActor.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "MovieWidget.h"
#include <../../../../../../../Source/Runtime/MediaAssets/Public/MediaPlayer.h>
//#include "MediaPlayer.h"
#include "MediaSource.h"

AWideMovieActor::AWideMovieActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	movieWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	movieWidget->SetupAttachment(rootComp);


}

void AWideMovieActor::BeginPlay()
{
	Super::BeginPlay();

	if (moviePlayer != nullptr)
	{
		// 미디어 소스를 미디어 플레이어에 넣는다.
		moviePlayer->OpenSource(movieSource);
	}

	// 위젯에 자신을 포인터로 가리키도록 해준다.
	Cast<UMovieWidget>(movieWidget->GetWidget())->movieActor = this;

	// 마우스 커서 표시하기
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	//moviePlayer->PlayAndSeek();



}

void AWideMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (moviePlayer->IsPlaying())
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), moviePlayer->GetDisplayTime().GetSeconds());
		UE_LOG(LogTemp, Warning, TEXT("%.2f"), moviePlayer->GetRate());
	}
}

void AWideMovieActor::Back()
{
	if (moviePlayer->IsPlaying() || moviePlayer->IsPaused())
	{
		if (moviePlayer->GetTime().GetTotalSeconds() > 10)
		{
			FTimespan newTime = moviePlayer->GetTime() - FTimespan(0, 0, 10);
			moviePlayer->Seek(newTime);
		}
		else
		{
			moviePlayer->Seek(FTimespan(0, 0, 0));
		}
	}
}

void AWideMovieActor::Stop()
{
	//UE_LOG(LogTemp, Warning, TEXT("Stop Actor!!"));

	if (moviePlayer->IsPlaying())
	{
		moviePlayer->Close();
	}
}

void AWideMovieActor::Play()
{
	//UE_LOG(LogTemp, Warning, TEXT("Play Actor!!"));

	if (moviePlayer->IsClosed())
	{
		moviePlayer->OpenSource(movieSource);
	}
	else if (moviePlayer->IsPlaying())
	{
		moviePlayer->Pause();
	}
	else if (moviePlayer->IsPaused())
	{
		moviePlayer->Play();
	}
	else
	{
		moviePlayer->Play();
	}
}

void AWideMovieActor::Forward()
{
	UE_LOG(LogTemp, Warning, TEXT("Forward Actor!!"));
	bool bCanSeek = moviePlayer->SupportsSeeking();
	UE_LOG(LogTemp, Warning, TEXT("Is Can Seek Function: %s"), bCanSeek ? *FString("True") : *FString("False"));


	if (moviePlayer->IsPlaying() || moviePlayer->IsPaused())
	{
		FTimespan newTime = moviePlayer->GetDisplayTime() + FTimespan(0, 0, 10);
		//UE_LOG(LogTemp, Warning, TEXT("NewTime: %d : %d : %d"), newTime.GetHours(), newTime.GetMinutes(), newTime.GetSeconds());

		bool isSeek = moviePlayer->Seek(newTime);
		UE_LOG(LogTemp, Warning, TEXT("Player Seek: %s"), isSeek ? *FString("True") : *FString("False"));

		UE_LOG(LogTemp, Warning, TEXT("is playing: %s"), moviePlayer->IsPlaying() ? *FString("True") : *FString("False"));
		UE_LOG(LogTemp, Warning, TEXT("is paused: %s"), moviePlayer->IsPaused() ? *FString("True") : *FString("False"));
		UE_LOG(LogTemp, Warning, TEXT("is ready: %s"), moviePlayer->IsReady() ? *FString("True") : *FString("False"));
		moviePlayer->Play();

	}
}

