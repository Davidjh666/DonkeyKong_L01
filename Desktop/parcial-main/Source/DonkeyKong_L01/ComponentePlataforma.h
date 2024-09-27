// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComponentePlataforma.generated.h"

class UStaticMeshComponent;

UCLASS()
class DONKEYKONG_L01_API AComponentePlataforma : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AComponentePlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//PROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* meshPlataforma;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoverActor(float DeltaTime);
	void MoverActorarriba_abajo(float DeltaTime);

	float MovimientoY = 0.0f;
	float MovimientoZ = 0.0f;
	float Velocidad = 100.0f;
	bool Direccion = true;
	bool bShouldMove = false;
	bool bShouldMovearriba_abajo = false;
	
};
