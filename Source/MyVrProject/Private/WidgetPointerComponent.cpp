// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetInteractionComponent.h"


UWidgetPointerComponent::UWidgetPointerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UWidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

}


void UWidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWidgetPointerComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Started, this, &UWidgetPointerComponent::MouseLeftClick);
	enhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Completed, this, &UWidgetPointerComponent::MouseLeftRelease);
}

void UWidgetPointerComponent::MouseLeftClick(const FInputActionValue& value)
{
	// 오른손 위젯 인터렉션 포인터에 마우스 왼쪽 클릭 효과를 부여한다.
	player->rightPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void UWidgetPointerComponent::MouseLeftRelease(const FInputActionValue& value)
{
	player->rightPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}

