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

	// �� ���� �׸� ��ư�� �� �� ������ ��
	if (bIsLeftGrip && bIsRightGrip)
	{
		UE_LOG(LogTemp, Warning, TEXT("Both On"));
		float degree = GetControllerAngle(player->leftController->GetComponentLocation(), player->rightController->GetComponentLocation(), player->GetActorRightVector());

		// �α� ǥ��
		player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("Angle: %d"), (int32)degree)));

		// ���� ȸ����Ű��
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

// ���� ���� ���͸� �̿��ؼ� �޼հ� �������� ���� ���̸� ����ؼ� ��ȯ�ϴ� �Լ�
float UCarCotrollerComponent::GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection)
{
	FVector handVector = (rightControllerLoc - leftControllerLoc).GetSafeNormal();
	FVector baseVector = baseDirection.GetSafeNormal();

	float dotResult = FVector::DotProduct(handVector, baseVector);
	float degree = FMath::RadiansToDegrees(FMath::Acos(dotResult));
	//UE_LOG(LogTemp, Warning, TEXT("Calc Angle: %.1f"), degree);

	// ���� ���Ϳ� ������ ����� ����̸� �������� ���� �ö� ����, ������ �������� �Ʒ��� ������ ����
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

