// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "WideMovieActor.h"


void UMovieWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư�� Ŭ���ϴ� �̺�Ʈ�� �Լ��� �����Ѵ�.
	btn_back->OnClicked.AddDynamic(this, &UMovieWidget::Back10Seconds);
	btn_stop->OnClicked.AddDynamic(this, &UMovieWidget::StopMovie);
	btn_play->OnClicked.AddDynamic(this, &UMovieWidget::PlayMovie);
	btn_forward->OnClicked.AddDynamic(this, &UMovieWidget::Forward10Seconds);
}

void UMovieWidget::Back10Seconds()
{
	if (movieActor != nullptr)
	{
		movieActor->Back();
	}
}

void UMovieWidget::StopMovie()
{
	//UE_LOG(LogTemp, Warning, TEXT("Stop Widget!!"));
	if (movieActor != nullptr)
	{
		movieActor->Stop();
	}
}

void UMovieWidget::PlayMovie()
{
	//UE_LOG(LogTemp, Warning, TEXT("Play Widget!!"));
	if (movieActor != nullptr)
	{
		movieActor->Play();
	}
}

void UMovieWidget::Forward10Seconds()
{
	if (movieActor != nullptr)
	{
		movieActor->Forward();
	}
}
