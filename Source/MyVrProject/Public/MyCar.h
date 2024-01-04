// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCar.generated.h"

UCLASS()
class MYVRPROJECT_API AMyCar : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyCar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UStaticMeshComponent* meshComp;

	void RotateCar(float angle);
};
