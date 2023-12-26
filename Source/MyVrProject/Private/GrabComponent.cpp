// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "Components/TextRenderComponent.h"
#include "PickUpActor.h"


UGrabComponent::UGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

}


void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGrabComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[1], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
}

void UGrabComponent::GrabObject()
{
	//player->rightLog->SetText(FText::FromString(FString("Try Grabbed!")));

	UWorld* world = GetWorld();
	
#pragma region 1. 라인 트레이스를 이용할 경우

	if (world != nullptr)
	{
		FHitResult hitInfo;
		FVector startLoc = player->rightHand->GetComponentLocation();
		FVector endLoc = startLoc + player->rightHand->GetRightVector() * 30.0f;

		if (world->LineTraceSingleByProfile(hitInfo, startLoc, endLoc, FName("PickUpPreset")))
		{
			APickUpActor* pickedObject = Cast<APickUpActor>(hitInfo.GetActor());

			if (pickedObject != nullptr)
			{
				pickedObject->Grabbed(player->rightHand);
			}
		}
	}
#pragma endregion

	// 2. 스피어 트레이스를 이용할 경우

	// 3. 오버랩 스피어를 이용할 경우

}

