// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "ClimbComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UClimbComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UClimbComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs);
	
private:
	bool bIsLeftGrip = false;
	bool bIsRightGrip = false;
	bool bClimbHandLeft = false;
	class AVR_Player* player;
	FVector prevHandLoc;
	
	void ClimbGrabLeft(const FInputActionValue& value);
	void ClimbGrabLeftOff(const FInputActionValue& value);
	void ClimbGrabRight(const FInputActionValue& value);
	void ClimbGrabRightOff(const FInputActionValue& value);

	bool GrabHandleCheck(class UMotionControllerComponent* hand);
};
