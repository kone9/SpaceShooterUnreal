// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	UPROPERTY(EditAnywhere)
	float WINDOW_SIZE_Y_CPP {1000};

	UPROPERTY(EditAnywhere)
	FVector2D SPEED_CPP {FVector2D(800,1200)};

	UPROPERTY(EditAnywhere)
	int health_CPP {2};

	UPROPERTY(EditAnywhere)
	int dir_CPP {-1};

	UPROPERTY(EditAnywhere)
    class USoundBase* hitSound{nullptr};

	UPROPERTY(EditAnywhere)
    class USoundBase* explosionSound{nullptr};

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem *ExplosionMeteor{nullptr};

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem *ExplosionFire{nullptr};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void RandomDirection();

	UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


	void MoveClamp_Y(float DeltaTime);

	void DestroyMeteor();

	void DescountLives();

private:
	class USphereComponent* ref_Collision{nullptr};




};
