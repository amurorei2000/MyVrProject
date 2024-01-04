// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AMyCar::AMyCar()
{
	PrimaryActorTick.bCanEverTick = false;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(2, 0.8f, 1.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

}

void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCar::RotateCar(float angle)
{
	//SetActorRotation(GetActorRotation() + FRotator(0, angle, 0));
	SetActorRotation(FRotator(0, angle, 0));
}

