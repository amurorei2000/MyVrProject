// Fill out your copyright notice in the Description page of Project Settings.


#include "VRHandAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"


void UVRHandAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 1. FMath Ŭ���� �Լ��� �̿��� ��
	// currentPoseAlpha ������ ���� PoseAlpha ������ ���� �ǵ��� ������(1��) �����Ѵ�.
	//CurrentPoseAlphaPoint_cpp = FMath::Lerp(CurrentPoseAlphaPoint_cpp, PoseAlphaPoint_cpp, DeltaSeconds * 13.0f);
	//CurrentPoseAlphaThumbUp_cpp = FMath::Lerp(CurrentPoseAlphaThumbUp_cpp, PoseAlphaThumbUp_cpp, DeltaSeconds *13.0f);


	// 2. KismetMathLibrary Ŭ���� �Լ��� �̿��� ��
	UKismetMathLibrary::FInterpTo(CurrentPoseAlphaPoint_cpp, PoseAlphaPoint_cpp, DeltaSeconds, 13);
	UKismetMathLibrary::FInterpTo(CurrentPoseAlphaThumbUp_cpp, PoseAlphaThumbUp_cpp, DeltaSeconds, 13);
}
