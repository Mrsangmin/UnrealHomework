// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveFloor.h"

// Sets default values
AMoveFloor::AMoveFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_TableRound.SM_TableRound"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Props/Materials/M_TableRound.M_TableRound"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	SpeedX = 300.0f;
	MaxRangeX = 800.0f;
}

// Called when the game starts or when spawned
void AMoveFloor::BeginPlay()
{
	Super::BeginPlay();
	FVector NewLocation(500.0f, 300.0f, 100.0f);
}

// Called every frame
void AMoveFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!FMath::IsNearlyZero(SpeedX))
	{
		FVector NewLocation = GetActorLocation() + FVector(SpeedX * DeltaTime, 0.0f, 0.0f);

		// 만약 위치가 제한을 넘어서면 방향을 반대로 변경
		if (NewLocation.X > MaxRangeX || NewLocation.X < -MaxRangeX)
		{
			SpeedX = -SpeedX; // 방향 반전
		}

		SetActorLocation(NewLocation);

	}
	
}



