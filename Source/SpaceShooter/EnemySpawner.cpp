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
	Spawner();

}




void AEnemySpawner::Spawner()
{
	UKismetSystemLibrary::K2_SetTimer(GetWorld(),TEXT("SpawnerEvent"),TimeDelaySpawn,true);//timer constante para instanciar
}


void AEnemySpawner::SpawnerEvent()
{
	if(!IsValid(GetWorld())) return;

	TSubclassOf<AActor> nuevaInstancia { RandomEnemy() };
	//GetWorld()->SpawnActor<AActor*>( refAsteroid);

}


void AEnemySpawner::save_arrows_transform()
{
	TArray<USceneComponent*> Children;

	GetRootComponent()->GetChildrenComponents(false,Children);

	if(Children.Num() > 0)
	{
		for(int i = 0; i< Children.Num(); i++)
		{
			if( !IsValid(Children[i])) return;
			points.Push( Children[i]->GetComponentTransform());
		}
	}

}


// Called every frame
TSubclassOf<AActor> AEnemySpawner::RandomEnemy()
{
	if( UKismetMathLibrary::RandomFloatInRange(0,1) < Probabilidad_Meteor)
	{
		return refAsteroid;
	}
	else
	{
		return refEnemy;
	}
}




// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

