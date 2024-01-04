// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CarCotrollerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UCarCotrollerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCarCotrollerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs);

private:
	class AVR_Player* player;
	
	bool bIsLeftGrip = false;
	bool bIsRightGrip = false;


	float GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection);
	void GripLeftOn();
	void GripLeftOff();
	void GripRightOn();
	void GripRightOff();
};
