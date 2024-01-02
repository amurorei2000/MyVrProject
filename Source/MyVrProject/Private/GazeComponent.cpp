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

	// ����, �ü� ���⿡ ��ü�� �ִٸ� ������ �������� ũ�⸦ ������Ų��(MaxSize������).
	if (GazeCheck())
	{
		currentSize += DeltaTime;
	}
	// �׷��� �ʴٸ� ������ �������� ũ�⸦ ���ҽ�Ų��(MinSize������).
	else
	{
		currentSize -= DeltaTime;
	}

	// Ŭ������ �����ϱ�
	//currentSize = FMath::Clamp(currentSize, 0.1f, 1.0f);
	//player->gazeMeshComp->SetWorldScale3D(baseSize * currentSize);
	
	// Lerp�� �����ϱ�
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

