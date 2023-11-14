// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h" // Include the Niagara Function Library header


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

	MoveClamp_Z(DeltaTime);

}

void AAsteroid::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if(health_CPP > 1)
	{
		DescountLives();
		CalculeChangeDirectionOverlap(OtherComp);
	}
	else
	{
		DestroyMeteor();
	}

}

void AAsteroid::MoveClamp_Z(float DeltaTime)
{
	MoveAsteroid(DeltaTime);
	CalculeInvertClangPositionZ();
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

void AAsteroid::DestroyMeteor()
{
	if( !IsValid(explosionSound)) return;
	if( !IsValid(ExplosionMeteor)) return;
	if( !IsValid(ExplosionFire)) return;
	if( !IsValid(GetWorld())) return;
	UGameplayStatics::PlaySound2D(GetWorld(),explosionSound);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ExplosionMeteor,GetActorLocation(),GetActorRotation(),GetActorScale());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ExplosionFire,GetActorLocation(),GetActorRotation(),GetActorScale());
	Destroy();
}

void AAsteroid::DescountLives()
{
	
	//
	if( !IsValid(hitSound)) return;
	health_CPP -=1;
	UGameplayStatics::PlaySound2D(GetWorld(),hitSound);
}

void AAsteroid::CalculeInvertClangPositionZ()
{
	if(GetActorLocation().Z > WINDOW_SIZE_Y_CPP + 850)
	{
		dir_CPP = 1;
	}

	if(GetActorLocation().Z < (WINDOW_SIZE_Y_CPP * -1) )
	{
		dir_CPP = -1;
	}
}

void AAsteroid::CalculeChangeDirectionOverlap(UPrimitiveComponent* OverlappedComponent)
{
	if(OverlappedComponent->GetOwner()->IsPendingKillEnabled())//si el actor esta aun en memoria enable
	{	
		if(!OverlappedComponent->ComponentHasTag("ball"))
		{
			dir_CPP = dir_CPP * -1;
		}
	}
}

void AAsteroid::MoveAsteroid(float DeltaTime)
{
	FVector new_position { GetActorLocation()};

	new_position.X = GetActorLocation().X - (SPEED_CPP.X * DeltaTime);
	new_position.Z = GetActorLocation().Z
	  - (dir_CPP * SPEED_CPP.Y * DeltaTime ) ; 

	SetActorLocation(new_position);
	AddActorWorldRotation(FRotator(0.5f,0,0));
}
