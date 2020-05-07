// Fill out your copyright notice in the Description page of Project Settings.

// terrain class
#include "PG_Terrain.h"

// extra classes
#include "Engine/World.h"
#include <TrollGame/Chunk.h>

// Sets default values
APG_Terrain::APG_Terrain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	flat_ground = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("flat_ground"));
	hill_ground = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("hill_ground"));

	flat_ground->SetupAttachment(RootComponent);
	hill_ground->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APG_Terrain::BeginPlay()
{
	Super::BeginPlay();

	build();

}

// Called every frame
void APG_Terrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// used to build the visuals of the terrain
void APG_Terrain::build() {
	loaded_chunks.Empty();

	UWorld* world = GetWorld();

	for (int i = 0; i <= visible; i++) {
		for (int j = 0; j <= visible; j++) {
			FVector tran = FVector(i, j, 0);
			FRotator rot = FRotator(0, 0, 0);
			AChunk* new_chunk = (AChunk*)world->SpawnActor(AChunk::StaticClass(), &tran);
			new_chunk->re_construct(i, j, component_len, r_seed, flat_ground, hill_ground);
			loaded_chunks.Add(new_chunk);
		}
	}
}
