// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "VR_Player.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "VRDrawFunctionLibrary.h"


UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

}


void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Triggered, this, &UMoveComponent::ShowLine);
	enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Completed, this, &UMoveComponent::Teleport);
}

// ������ ���̰� �ϴ� �Լ�
void UMoveComponent::ShowLine(const FInputActionValue& value)
{
	bool bIsPressed = value.Get<bool>();
	//player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("%s"), bIsPressed ? *FString("Pressed!") : *FString("Released..."))));

	if (bIsPressed && player != nullptr)
	{
		DrawTrajectory(player->leftController->GetComponentLocation(), player->leftHand->GetForwardVector() * -1 + player->leftHand->GetRightVector(), lineSpeed, 50, 0.1f);
	}
}

// ���� ���� ����ϰ� �׸��� �Լ�(�߷� ���)
void UMoveComponent::DrawTrajectory(FVector startLoc, FVector dir, float speed, int32 segment, float interval)
{
	TArray<FVector> linePositions;

	for (int32 i = 0; i < segment; i++)
	{
		// dir �������� segment ȸ��ŭ interval ����(��)���� �ݺ��ؼ� �̵����� ��ġ�� ����Ѵ�.
		float elapsedTime = interval * i;
		FVector gravityVec = FVector(0, 0, GetWorld()->GetDefaultGravityZ());
		FVector newLocation = startLoc + dir * speed * elapsedTime + (0.5f * gravityVec * elapsedTime * elapsedTime);

		FHitResult hitInfo;
		if (i > 0 && GetWorld()->LineTraceSingleByChannel(hitInfo, linePositions[i - 1], newLocation, ECC_Visibility))
		{
			player->leftLog->SetText(FText::FromString(hitInfo.GetActor()->GetActorNameOrLabel()));

			linePositions.Add(hitInfo.ImpactPoint);
			break;
		}

		// ��� ��� ������ �迭 ������ ��Ƴ��´�.
		linePositions.Add(newLocation);

	}

	// ���� ��ġ���� ������ �����ؼ� �׸���.
	for (int32 i = 0; i < linePositions.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), linePositions[i], linePositions[i + 1], FColor::Green, false, 0, 0, 2.0f);

	}

	// ������ ��ġ�� ���� ���ڸ� ǥ���Ѵ�.
	targetLocation = linePositions[linePositions.Num() - 1];
	DrawDebugSolidBox(GetWorld(), targetLocation, FVector(5), FColor::Red);
}

void UMoveComponent::DrawTrajectoryBezier(FVector startLoc, FVector dir, int32 segment)
{
	//TArray<FVector> results = UVRDrawFunctionLibrary::CalculateBezierCurve();
}

// ��ǥ �������� �����̵��ϴ� �Լ�
void UMoveComponent::Teleport()
{
	// Black Fade In ȿ���� �ش�.
	player->GetController<APlayerController>()->PlayerCameraManager->StartCameraFade(0, 1.0f, teleportDelay, FLinearColor::Black);
	
	if (!targetLocation.IsNearlyZero())
	{
		FTimerHandle teleportTimer;

		GetWorld()->GetTimerManager().SetTimer(teleportTimer, FTimerDelegate::CreateLambda([&]() {
			player->SetActorLocation(targetLocation + FVector(0, 0, player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
			}), teleportDelay, false);
	}
}

