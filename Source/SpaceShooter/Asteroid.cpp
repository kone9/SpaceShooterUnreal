// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"


// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	ref_Collision = Cast<USphereComponent>( GetComponentByClass(USphereComponent::StaticClass()) );
	if( !IsValid(ref_Collision)) return;
	ref_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnComponentBeginOverlap);	


	RandomDirection();
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveClamp_Y(DeltaTime);
	
}


void AAsteroid::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if( !IsValid(GetWorld())) return;
	
	health_CPP -=1;

	if(health_CPP < 1)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "SE DESTRUYE EL ASTEROIDE");
		//|Destroy();
	}

}




void AAsteroid::MoveClamp_Y(float DeltaTime)
{

	FVector new_position { GetActorLocation()};

	new_position.X = GetActorLocation().X - (SPEED_CPP.X * DeltaTime);
	new_position.Z = GetActorLocation().Z  - (dir_CPP * SPEED_CPP.Y * DeltaTime ) ; 

	SetActorLocation(new_position);
	AddActorWorldRotation(FRotator(0.5f,0,0));


	if(GetActorLocation().Z > WINDOW_SIZE_Y_CPP + 850)
	{
		dir_CPP = 1;
	}

	if(GetActorLocation().Z < (WINDOW_SIZE_Y_CPP * -1) )
	{
		dir_CPP = -1;
	}


}


void AAsteroid::RandomDirection()
{

	if(UKismetMathLibrary::RandomFloatInRange(0,1) < 0.5f)
	{
		dir_CPP = -1;
	}
	else
	{
		dir_CPP = 1;
	}

}






