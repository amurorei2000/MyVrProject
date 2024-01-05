// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AHandleActor::AHandleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(0.15f));
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel4);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Ignore);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AHandleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHandleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

