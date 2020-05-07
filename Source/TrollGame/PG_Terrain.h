// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// actor classes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// my extra classes
#include <TrollGame/Chunk.h>
#include "Components/InstancedStaticMeshComponent.h"

// all includes above here
#include "PG_Terrain.generated.h"


UCLASS()
class TROLLGAME_API APG_Terrain : public AActor
{
	GENERATED_BODY()

private:

public:
	// Sets default values for this actor's properties
	APG_Terrain();

	UPROPERTY(EditAnywhere)
		int64 r_seed = 1;

	UPROPERTY(EditAnywhere)
		int64 visible = 2;

	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* flat_ground;
	UPROPERTY(EditAnywhere)
		UInstancedStaticMeshComponent* hill_ground;
	UPROPERTY(EditAnywhere)
		int64 component_len = 800;

	UPROPERTY()
		TArray<AChunk*> loaded_chunks{};

	void build();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
