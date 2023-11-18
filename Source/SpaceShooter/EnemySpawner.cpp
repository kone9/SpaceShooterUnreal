// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	save_arrows_transform();
	SpawnerTimer();

}


void AEnemySpawner::SpawnerTimer()
{
	UKismetSystemLibrary::K2_SetTimer(this,TEXT("SpawnerEnemy"),time_delay_spawnCPP,true);//timer constante para instanciar
}


void AEnemySpawner::SpawnerEnemy()
{
	// UKismetSystemLibrary::PrintString(GetWorld(),"INSTANCIANDO ENEMIGO CPP");
	if(!IsValid(GetWorld())) return;


	if (pointsCPP.Num() > 0) // instancia en punto aleatorio
	{
		TSubclassOf<AActor> nuevaInstancia { RandomEnemy() };

		FActorSpawnParameters spawn_params{};
		spawn_params.Owner = nullptr; // Specify owner actor for this new actor if you need one.
		spawn_params.Instigator = nullptr; // Specify instigator pawn for this new actor if you need one
		spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		int32 RandomTransformIndex = UKismetMathLibrary::RandomIntegerInRange(0, pointsCPP.Num() - 1);

		if (!IsValid(nuevaInstancia)) return;

		GetWorld()->SpawnActor<AActor>(nuevaInstancia, pointsCPP[RandomTransformIndex], spawn_params);
	}
}


void AEnemySpawner::save_arrows_transform()
{
	TArray<USceneComponent*> ChildrenArrowsPositionsSpawns;

	GetRootComponent()->GetChildrenComponents(false,ChildrenArrowsPositionsSpawns);

	if(ChildrenArrowsPositionsSpawns.Num() > 0)
	{
		for(int i = 0; i< ChildrenArrowsPositionsSpawns.Num(); i++)
		{
			if( !IsValid(ChildrenArrowsPositionsSpawns[i])) return;
			pointsCPP.Push( ChildrenArrowsPositionsSpawns[i]->GetComponentTransform());
		}
	}

}


// Called every frame
TSubclassOf<AActor> AEnemySpawner::RandomEnemy()
{
	if( UKismetMathLibrary::RandomFloatInRange(0,1) < probabilidad_meteorCPP)
	{
		return refAsteroidCPP;
	}
	else
	{
		return refEnemyCPP;
	}
}




// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
}

