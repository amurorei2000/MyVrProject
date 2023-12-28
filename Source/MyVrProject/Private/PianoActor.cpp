// Fill out your copyright notice in the Description page of Project Settings.

#include "PianoActor.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "KeyboardActor.h"


APianoActor::APianoActor()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	float width = (5 * 8) + (3 * (8 - 1));
	FVector startLoc = FVector(0, width * 0.5f * -1 + 2.5f, 0);

	for (int32 i = 0; i < 8; i++)
	{
		FString actorName = FString::Printf(TEXT("Keyboard_%d"), i + 1);
		UChildActorComponent* children = CreateDefaultSubobject<UChildActorComponent>(FName(*actorName));
		children->SetupAttachment(RootComponent);
		keyActors.Add(children);

		children->SetRelativeLocation(startLoc + FVector(0, 8 * i, 0));
	}
}

void APianoActor::BeginPlay()
{
	Super::BeginPlay();

	// 각각의 키보드 액터들마다 가지고 있는 keySound 변수에 음원 파일들을 넣어준다.
	for (int32 i = 0; i < keySounds.Num(); i++)
	{
		if (keyActors[i]->GetChildActor() != nullptr)
		{
			Cast<AKeyboardActor>(keyActors[i]->GetChildActor())->keySound = keySounds[i];
		}
	}
}

void APianoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

