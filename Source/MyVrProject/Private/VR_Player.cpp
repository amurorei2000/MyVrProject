// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/TextRenderComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "MoveComponent.h"


AVR_Player::AVR_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(RootComponent);

	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(cameraComp);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	leftController->SetupAttachment(RootComponent);
	leftController->SetRelativeLocation(FVector(50, -30, -10));
	leftController->SetTrackingMotionSource(FName("Left"));

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(-90, -45, -180));

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftHand);
	leftLog->SetRelativeLocation(FVector(-20, 10, 0));
	leftLog->SetRelativeRotation(FRotator(0, -90, -90));
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	leftLog->SetWorldSize(20);
	leftLog->SetTextRenderColor(FColor(255, 255, 0));

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->SetRelativeLocation(FVector(50, 30, -10));
	rightController->SetTrackingMotionSource(FName("Right"));

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(90, 45, 0));

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightHand);
	rightLog->SetRelativeLocation(FVector(20, 10, 0));
	rightLog->SetRelativeRotation(FRotator(0, -90, 90));
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetWorldSize(20);
	rightLog->SetTextRenderColor(FColor(255, 255, 0));

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// ���� ������Ʈ
	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("Move Component"));

}

void AVR_Player::BeginPlay()
{
	Super::BeginPlay();

	// ��� ����Ʈ ���÷��� ����� Ʈ��ŷ(����) ���� ��ġ�� Stage�� �����Ѵ�.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	// �Է� ���� �����ϱ�
	if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr && imc != nullptr)
		{
			subsys->AddMappingContext(imc, 0);
		}
	}
}

void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ���� �Է� �����͸� Enhanced �Է� ������ ���·� ��ȯ�Ѵ�.
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		// �Է� Ű ���ε��ϱ�
		/*enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Touch);
		enhancedInputComponent->BindAction(ia_rightTriggerTouch, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Touch);
		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Bool);
		enhancedInputComponent->BindAction(ia_rightTriggerBool, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Bool);*/
		/*enhancedInputComponent->BindAction(ia_rightTriggerFloat, ETriggerEvent::Triggered, this, &AVR_Player::RightTriggerInput_Float);
		enhancedInputComponent->BindAction(ia_rightTriggerFloat, ETriggerEvent::Completed, this, &AVR_Player::RightTriggerInput_Float);
		enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Triggered, this, &AVR_Player::RightThumbstickInput);
		enhancedInputComponent->BindAction(ia_rightThumbStick, ETriggerEvent::Completed, this, &AVR_Player::RightThumbstickInput);
		enhancedInputComponent->BindAction(ia_moveInput, ETriggerEvent::Triggered, this, &AVR_Player::PlayerMove);
		enhancedInputComponent->BindAction(ia_rotateInput, ETriggerEvent::Triggered, this, &AVR_Player::PlayerRotate)*/;

		// ������Ʈ�� �Է� �̺�Ʈ �Ѱ��ֱ�
		moveComp->SetupPlayerInputComponent(enhancedInputComponent, ia_inputs);
	}
}

void AVR_Player::RightTriggerInput_Bool(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Pressed!")));
	}
	else
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Released!")));
	}

}

void AVR_Player::RightTriggerInput_Float(const FInputActionValue& value)
{
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("RightTrigger : %.2f"), value.Get<float>())));

	BasicTeleport(500, rightController->GetForwardVector(), rightController->GetComponentLocation());
}

void AVR_Player::RightTriggerInput_Touch(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Touched!")));
	}
	else
	{
		rightLog->SetText(FText::FromString(FString("RightTrigger Untouched!")));
	}
}

void AVR_Player::RightThumbstickInput(const FInputActionValue& value)
{
	FVector2D inputValue = value.Get<FVector2D>();
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\r\nY: %.2f"), inputValue.X, inputValue.Y)));
}

void AVR_Player::PlayerMove(const FInputActionValue& value)
{
	// 1. �÷��̾ �Է�(��w��s��a��d + �潺ƽ)�Ѵ��
	FVector inputDir = FVector(value.Get<FVector2D>().X, value.Get<FVector2D>().Y, 0);
	//UE_LOG(LogTemp, Log, TEXT("X: %.2f, Y: %.2f, Z: %.2f"), inputDir.X, inputDir.Y, inputDir.Z);

	// 2. ȸ���� ���� ���� ���¿����� ������ ���� ȸ���� ���⿡ ���� ��ȯ�Ѵ�.
	FVector modifiedDir = GetTransform().TransformVector(inputDir);

	// 3. �̵��Ѵ�.
	AddMovementInput(modifiedDir);
}

void AVR_Player::PlayerRotate(const FInputActionValue& value)
{
	// �Է�(�¿�: mouse ���� ����)�Ѵ�� 
	float inputDir = value.Get<float>();

	// ȸ���Ѵ�.
	AddControllerYawInput(inputDir);
}

void AVR_Player::BasicTeleport(float sightRange, FVector direction, FVector pivot)
{
	// ����Ų ����(direction �������� sightRange �Ÿ���ŭ �߻��� ������ ���� ���� ����)����

	FHitResult hitInfo;
	FVector startVec = pivot;
	FVector endVec = pivot + direction * sightRange;
	bool bIsCollide = GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endVec, ECC_Visibility);

	// ����, ��Ҵٸ� ���� �̵���Ų��.
	if (bIsCollide)
	{
		//SetActorLocation(hitInfo.ImpactPoint + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

		// ��Ҵٸ� ���� �������� ������ �׸���.
		DrawDebugLine(GetWorld(), startVec, hitInfo.ImpactPoint, FColor::Red);
	}
	// ���� �ʾҴٸ� �ִ� �������� ������ �׸���.
	else 
	{
		DrawDebugLine(GetWorld(), startVec, endVec, FColor::Red);
	}

	
}
