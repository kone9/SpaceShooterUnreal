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
	TArray<FTransform> pointsCPP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> refEnemyCPP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> refAsteroidCPP;

	UPROPERTY(EditAnywhere)
	float probabilidad_meteorCPP{0.1f};

	UPROPERTY(EditAnywhere)
	float time_delay_spawnCPP{1.0f};


	UFUNCTION()
    void SpawnerEnemy();

private:
    void SpawnerTimer();
	

    void save_arrows_transform();

    TSubclassOf<AActor> RandomEnemy();




};
