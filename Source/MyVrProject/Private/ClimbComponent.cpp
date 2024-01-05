// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "EnhancedInputComponent.h"
#include "MotionControllerComponent.h"
#include "VR_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

UClimbComponent::UClimbComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UClimbComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVR_Player>();
}


void UClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//player->SetActorLocation(player->GetActorLocation() + FVector(0, 0, 1));
	//player->OffsetActor(FVector::UpVector);

	if (bIsLeftGrip || bIsRightGrip)
	{
		FVector currentHandLocation = bClimbHandLeft ? player->leftController->GetComponentLocation() : player->rightController->GetComponentLocation();

		FVector delta = prevHandLoc - currentHandLocation;
		player->GetCharacterMovement()->GravityScale = 0;
		prevHandLoc = bClimbHandLeft ? player->leftController->GetComponentLocation() : player->rightController->GetComponentLocation();

		UE_LOG(LogTemp, Warning, TEXT("delta x: %f, y: %f, z: %f"), prevHandLoc.X, prevHandLoc.Y, prevHandLoc.Z);
		player->AddActorWorldOffset(delta);
	}
	else
	{
		player->GetCharacterMovement()->GravityScale = 1.0f;
	}

}

void UClimbComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[12], ETriggerEvent::Started, this, &UClimbComponent::ClimbGrabLeft);
	enhancedInputComponent->BindAction(inputs[12], ETriggerEvent::Completed, this, &UClimbComponent::ClimbGrabLeftOff);
	enhancedInputComponent->BindAction(inputs[13], ETriggerEvent::Started, this, &UClimbComponent::ClimbGrabRight);
	enhancedInputComponent->BindAction(inputs[13], ETriggerEvent::Completed, this, &UClimbComponent::ClimbGrabRightOff);
}

void UClimbComponent::ClimbGrabLeft(const FInputActionValue& value)
{
	if (GrabHandleCheck(player->leftController))
	{
		bIsLeftGrip = value.Get<bool>();
		bClimbHandLeft = true;
		
		if (bIsLeftGrip)
		{
			prevHandLoc = player->leftController->GetComponentLocation();
		}
	}
}

void UClimbComponent::ClimbGrabLeftOff(const FInputActionValue& value)
{
	bIsLeftGrip = false;
}

void UClimbComponent::ClimbGrabRight(const FInputActionValue& value)
{
	if (GrabHandleCheck(player->rightController))
	{
		bIsRightGrip = value.Get<bool>();
		//UE_LOG(LogTemp, Warning, TEXT("Collide Handle Right!"));
		bClimbHandLeft = false;
		if (bIsRightGrip)
		{
			prevHandLoc = player->rightController->GetComponentLocation();
		}
	}
}

void UClimbComponent::ClimbGrabRightOff(const FInputActionValue& value)
{
	bIsRightGrip = false;
}

bool UClimbComponent::GrabHandleCheck(UMotionControllerComponent* hand)
{
	FVector startLoc = hand->GetComponentLocation();
	FHitResult hitInfo;
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_GameTraceChannel4);

	return GetWorld()->SweepSingleByObjectType(hitInfo, startLoc, startLoc, FQuat::Identity, params, FCollisionShape::MakeSphere(10));
}

