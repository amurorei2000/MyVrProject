// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GazeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UGazeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGazeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category="MySettings")
	FVector minSize = FVector(0.1f);

	UPROPERTY(EditAnywhere, Category="MySettings")
	FVector maxSize = FVector(1.0f);
		
private:
	class AVR_Player* player;
	float currentSize = 0;
	bool GazeCheck();
	FVector baseSize;
};
