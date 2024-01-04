// Fill out your copyright notice in the Description page of Project Settings.


#include "CarCotrollerComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "MyCar.h"


UCarCotrollerComponent::UCarCotrollerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCarCotrollerComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

}


void UCarCotrollerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 양 손의 그립 버튼을 둘 다 눌렀을 때
	if (bIsLeftGrip && bIsRightGrip)
	{
		UE_LOG(LogTemp, Warning, TEXT("Both On"));
		float degree = GetControllerAngle(player->leftController->GetComponentLocation(), player->rightController->GetComponentLocation(), player->GetActorRightVector());

		// 로그 표시
		player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("Angle: %d"), (int32)degree)));

		// 차를 회전시키기
		player->controlledCar->RotateCar(degree);
	}

}

void UCarCotrollerComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Started, this, &UCarCotrollerComponent::GripLeftOn);
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Completed, this, &UCarCotrollerComponent::GripLeftOff);
	enhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Started, this, &UCarCotrollerComponent::GripRightOn);
	enhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Completed, this, &UCarCotrollerComponent::GripRightOff);
}

// 기준 방향 벡터를 이용해서 왼손과 오른손의 각도 차이를 계산해서 반환하는 함수
float UCarCotrollerComponent::GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection)
{
	FVector handVector = (rightControllerLoc - leftControllerLoc).GetSafeNormal();
	FVector baseVector = baseDirection.GetSafeNormal();

	float dotResult = FVector::DotProduct(handVector, baseVector);
	float degree = FMath::RadiansToDegrees(FMath::Acos(dotResult));
	//UE_LOG(LogTemp, Warning, TEXT("Calc Angle: %.1f"), degree);

	// 위쪽 벡터와 내적한 결과가 양수이면 오른손이 위로 올라간 벡터, 음수면 오른손이 아래로 내려간 벡터
	if (FVector::DotProduct(player->GetActorUpVector(), handVector) > 0)
	{
		degree *= -1.0f;
	}

	return degree;
}

void UCarCotrollerComponent::GripLeftOn()
{
	UE_LOG(LogTemp, Warning, TEXT("Left Grip On!"));
	
	bIsLeftGrip = true;
}

void UCarCotrollerComponent::GripLeftOff()
{
	UE_LOG(LogTemp, Warning, TEXT("Left Grip Off!"));
	
	bIsLeftGrip = false;
}

void UCarCotrollerComponent::GripRightOn()
{
	UE_LOG(LogTemp, Warning, TEXT("Right Grip On!"));
	
	bIsRightGrip = true;
}

void UCarCotrollerComponent::GripRightOff()
{
	UE_LOG(LogTemp, Warning, TEXT("Right Grip Off!"));
	bIsRightGrip = false;
}

