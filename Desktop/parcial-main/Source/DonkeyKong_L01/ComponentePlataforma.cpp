// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentePlataforma.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AComponentePlataforma::AComponentePlataforma()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("	StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	meshPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshPlataforma->SetStaticMesh(MeshAsset.Object);
	RootComponent = meshPlataforma;
	
	FVector NewScale(2.0f, 6.0f, 0.5f); // Cambia estos valores según tus necesidades
	SetActorScale3D(NewScale);

}

// Called when the game starts or when spawned
void AComponentePlataforma::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AComponentePlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoverActor(DeltaTime);
	MoverActorarriba_abajo(DeltaTime);
}

void AComponentePlataforma::MoverActor(float DeltaTime)
{

	if (!bShouldMove)
		return;
	FVector NuevaPosicion = GetActorLocation();

	if (Direccion)
	{
		MovimientoY += Velocidad * DeltaTime;
		if (MovimientoY >= 500.0f)
		{
			Direccion = false;
		}
	}
	else
	{
		MovimientoY -= Velocidad * DeltaTime;
		if (MovimientoY <= -500.0f)
		{
			Direccion = true;
		}
	}

	NuevaPosicion.Y = MovimientoY;
	SetActorLocation(NuevaPosicion);

}

void AComponentePlataforma::MoverActorarriba_abajo(float DeltaTime)
{

	if (!bShouldMovearriba_abajo)
		return;
	FVector NuevaPosicion = GetActorLocation();

	if (Direccion)
	{
		MovimientoY += Velocidad * DeltaTime;
		if (MovimientoZ >= 500.0f)
		{
			Direccion = false;
		}
	}
	else
	{
		MovimientoY -= Velocidad * DeltaTime;
		if (MovimientoZ <= -500.0f)
		{
			Direccion = true;
		}
	}

	NuevaPosicion.Z = MovimientoZ;
	SetActorLocation(NuevaPosicion);
}


