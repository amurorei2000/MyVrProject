// Fill out your copyright notice in the Description page of Project Settings.


#include "GazeComponent.h"
#include "VR_Player.h"
#include "Camera/CameraComponent.h"

UGazeComponent::UGazeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGazeComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();

	baseSize = player->gazeMeshComp->GetComponentScale();
}


void UGazeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 만일, 시선 방향에 물체가 있다면 게이즈 포인터의 크기를 증가시킨다(MaxSize까지만).
	if (GazeCheck())
	{
		currentSize += DeltaTime;
	}
	// 그렇지 않다면 게이즈 포인터의 크기를 감소시킨다(MinSize까지만).
	else
	{
		currentSize -= DeltaTime;
	}

	// 클램프로 구현하기
	//currentSize = FMath::Clamp(currentSize, 0.1f, 1.0f);
	//player->gazeMeshComp->SetWorldScale3D(baseSize * currentSize);
	
	// Lerp로 구현하기
	currentSize = FMath::Clamp(currentSize, 0.1f, 1.0f);
	FVector newSize = FMath::Lerp(minSize, maxSize, currentSize);
	player->gazeMeshComp->SetWorldScale3D(baseSize.X * newSize);

}



bool UGazeComponent::GazeCheck()
{
	FHitResult hitInfo;
	FVector startVec = player->cameraComp->GetComponentLocation();
	FVector endVec = startVec + player->cameraComp->GetForwardVector() * 1000.0f;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	return GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endVec, ECC_Visibility, params);
}

