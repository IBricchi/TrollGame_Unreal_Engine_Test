// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// actor classes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// my extra classes
#include "Components/InstancedStaticMeshComponent.h"

// all includes above here
#include "Chunk.generated.h"

UCLASS()
class TROLLGAME_API AChunk : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AChunk();
	AChunk(int64 _x, int64 _y, int64 _len, int64 _r_seed, UInstancedStaticMeshComponent* _flat_ground, UInstancedStaticMeshComponent* _hill_ground);

	UPROPERTY(EditAnywhere)
		int64 r_seed;

	UPROPERTY(EditAnywhere)
		int64 c_x;

	UPROPERTY(EditAnywhere)
		int64 c_y;

	UPROPERTY(EditAnywhere)
		int64 size;

	UPROPERTY(EditAnywhere)
		int64 len;

	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* flat_ground;
	
	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* hill_ground;

	float PerlinNoise(int64 x, int64 y);
	void re_construct(int64 _x, int64 _y, int64 _len, int64 _r_seed, UInstancedStaticMeshComponent* _flat_ground, UInstancedStaticMeshComponent* _hill_ground);
	void build();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
