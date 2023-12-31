// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandleActor.generated.h"

UCLASS()
class MYVRPROJECT_API AHandleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHandleActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UStaticMeshComponent* meshComp;
};
