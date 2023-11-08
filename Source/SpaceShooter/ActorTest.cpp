// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorTest.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"


// Sets default values
AActorTest::AActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	newRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootARiel"));
	RootComponent = newRoot;

	newCOmpoenent = CreateDefaultSubobject<UAudioComponent>(TEXT("ComponentCPPAriel"));
	newCOmpoenent->SetupAttachment(newRoot);

}

// Called when the game starts or when spawned
void AActorTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* jugador { UGameplayStatics::GetPlayerPawn(GetWorld(),0) };
	
	
	if(!IsValid(jugador)) return;

	FVector posicion { jugador->GetActorLocation()};
	
	MostrarPosicion(posicion);

}


void AActorTest::MostrarPosicion(FVector posicion)
{
	UKismetSystemLibrary::PrintString(GetWorld(),UKismetStringLibrary::Conv_VectorToString(posicion));
}