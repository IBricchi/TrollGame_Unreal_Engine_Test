// Fill out your copyright notice in the Description page of Project Settings.

// chunk class
#include "Chunk.h"

// extra classes
#include "Math/UnrealMathUtility.h"

// Sets default values
AChunk::AChunk() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	re_construct(0, 0, 800, 1, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("flat_ground")), CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("hill_ground")));
}

// Proper Constructer
AChunk::AChunk(int64 _x, int64 _y, int64 _len, int64 _r_seed, UInstancedStaticMeshComponent* _flat_ground, UInstancedStaticMeshComponent* _hill_ground)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	re_construct(_x, _y, _len, _r_seed, _flat_ground, _hill_ground);
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Call perlin noise function to generate random terrain
float AChunk::PerlinNoise(int64 x, int64 y) {
	FVector2D nv = FVector2D((c_x + x/size + r_seed) / 10.0f, (c_y + y/size + r_seed) / 10.0f);
	float n = FMath::PerlinNoise2D(nv);
	return n;
}

//re-construct chunk
void AChunk::re_construct(int64 _x, int64 _y, int64 _len, int64 _r_seed, UInstancedStaticMeshComponent* _flat_ground, UInstancedStaticMeshComponent* _hill_ground) {
	r_seed = _r_seed;
	c_x = _x;
	c_y = _y;
	len = _len;
	//if (flat_ground != nullptr) delete flat_ground;
	//flat_ground->SetStaticMesh(_flat_ground->GetStaticMesh());
	flat_ground = _flat_ground;
	//if (hill_ground != nullptr) delete hill_ground;
	//hill_ground->SetStaticMesh(_hill_ground->GetStaticMesh());
	hill_ground = _hill_ground;

	//flat_ground->SetupAttachment(RootComponent);
	//hill_ground->SetupAttachment(RootComponent);

	build();
}

// used to build visuals of AChunk
void AChunk::build() {
	UE_LOG(LogTemp, Warning, TEXT("building instance of AChunk"));

	hill_ground->ClearInstances();
	flat_ground->ClearInstances();

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			FVector tran_v{};
			tran_v.X = c_x * len + x * len;
			tran_v.Y = c_y * len + y * len;

			//UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), tran_v.X, tran_v.Y, len);

			FTransform tran(tran_v);

			if (PerlinNoise(x, y) > 0) {
				hill_ground->AddInstanceWorldSpace(tran);
			}
			else {
				flat_ground->AddInstanceWorldSpace(tran);
			}
		}
	}
}