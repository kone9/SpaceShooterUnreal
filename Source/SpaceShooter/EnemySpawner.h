// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SPACESHOOTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	TArray<FTransform> points;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> refEnemy;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> refAsteroid;

	UPROPERTY(EditAnywhere)
	float Probabilidad_Meteor{0.1f};

	UPROPERTY(EditAnywhere)
	float TimeDelaySpawn{1};




private:
    void Spawner();

    void SpawnerEvent();

    void save_arrows_transform();

    TSubclassOf<AActor> RandomEnemy();




};
