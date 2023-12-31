// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorTest.generated.h"

UCLASS()
class SPACESHOOTER_API AActorTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void MostrarPosicion(FVector posicion);


	UPROPERTY(EditAnywhere)
	FVector prueba{ FVector::UpVector};

	UPROPERTY(EditAnywhere)
	UAudioComponent* newCOmpoenent{nullptr};


	UPROPERTY(VisibleAnywhere)
	USceneComponent* newRoot{nullptr};


};
