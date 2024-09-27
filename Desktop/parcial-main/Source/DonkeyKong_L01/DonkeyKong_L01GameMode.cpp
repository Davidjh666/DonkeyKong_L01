// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L01GameMode.h"
#include "DonkeyKong_L01Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Obstaculo.h"
#include "ComponentePlataforma.h"
#include "Enemigo.h"

#include <ctime>	
#include <cstdlib>
#include <set> 

ADonkeyKong_L01GameMode::ADonkeyKong_L01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	obstaculo01 = nullptr;
	player01 = nullptr;

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		player01 = Cast<ADonkeyKong_L01Character>(PlayerPawnBPClass.Class);
	}
}

void ADonkeyKong_L01GameMode::BeginPlay()
{
	Super::BeginPlay();

	FVector posicionInicial = FVector(1160.0f, -1100.0f, 400.f);
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
	FTransform SpawnLocationCP;
	FTransform SpawnLocation6;
	FTransform SpawnLocation7;
	FTransform SpawnLocation8;
	FTransform SpawnLocationCP2;
	float anchoComponentePlataforma = 600.0f;
	float incrementoAltoComponentePlataforma = -105.0f;
	float incrementoAltoEntrePisos = 350.0f;
	float incrementoInicioPiso = 50.0f;
	int ncp = 0;









	for (int npp = 0; npp < 5; npp++) {
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
		if (npp % 2 == 0) {
			SpawnLocationCP.SetRotation(FQuat(rotacionInicial));

			for (ncp = 0; ncp < 15; ncp++) {
				SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));

				if (ncp < 14) {
					posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
				}


			}
		}
		else {
			// spawnear sin rotacion
			SpawnLocationCP2.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f))); // Asegurarse de que la rotación sea cero


			for (ncp = 0; ncp < 15; ncp++) {
				SpawnLocationCP2.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));

				if (ncp < 14) {
					posicionInicial.Z = posicionInicial.Z;
				}

			}
		}

		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;

		AComponentePlataforma* NewPlatform = GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), SpawnLocationCP2);
		if (NewPlatform)
		{
			componenteplataforma.Add(ncp + 1, NewPlatform);
		}

		srand(time(nullptr));

		std::set<int> numerosGenerados; // Conjunto para almacenar números generados
		int j = 0;
		for (int k = 0; k < 5; k++) {

			if (k == 0) {
				int q = 0;
				while (q < 2) {
					int RandomNumber = rand() % 15 + 1;

					if (numerosGenerados.find(RandomNumber) == numerosGenerados.end()) {

						if (RandomNumber == ncp) {
							NewPlatform->bShouldMove = true;
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("se mueve de izquierda a derecha"));
						}
						else {
							NewPlatform->bShouldMovearriba_abajo = true;
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("se mueve de arriba a abajo"));
						}
					}
				}




					//while (j < 3) { // Cambiamos la condición para que solo se ejecute 3 veces
					//	int RandomNumber = rand() % 5 + 1;

					//	// Verificamos si el número ya ha sido generado
					//	if (numerosGenerados.find(RandomNumber) == numerosGenerados.end()) {

					//		numerosGenerados.insert(RandomNumber); // Añadimos el número al conjunto

					//		if (RandomNumber == 1 && ncp + 1 == 1) {
					//			NewPlatform->bShouldMove = true;
					//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Se mueve la plataforma 1"));
					//		}
					//		else if (RandomNumber == 2 && ncp + 1 == 2) {
					//			NewPlatform->bShouldMove = true;
					//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Se mueve la plataforma 2"));
					//		}
					//		else if (RandomNumber == 3 && ncp + 1 == 3) {
					//			NewPlatform->bShouldMove = true;
					//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Se mueve la plataforma 3"));
					//		}
					//		else if (RandomNumber == 4 && ncp + 1 == 4) {
					//			NewPlatform->bShouldMove = true;
					//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Se mueve la plataforma 4"));
					//		}
					//		else if (RandomNumber == 5 && ncp + 1 == 5) {
					//			NewPlatform->bShouldMove = true;
					//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Se mueve la plataforma 5"));
					//		}

							j++; // Incrementamos el contador solo si el número es nuevo
					
					//}
				}
			}




		}
	}



void ADonkeyKong_L01GameMode::Tick(float DeltaTime)
{
}

