// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkParticleSystem.h"

// Sets default values
ANetworkParticleSystem::ANetworkParticleSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called when the game starts or when spawned
void ANetworkParticleSystem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANetworkParticleSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//// spawn particle System;
	//if (!isSpawned && UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(FKey("X"))) {
	//	SpawnParticles();
	//}

	//// Despawn particle System;
	//if (isSpawned && UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(FKey("C"))) {
	//	DeSpawnParticles();
	//}
}

void ANetworkParticleSystem::SpawnParticles_Implementation(const FString& oscPath)
{
	int indexLocation = -1;
	if (oscPath.FindLastChar('/', indexLocation)) {
		FString indexString = oscPath.RightChop(3);
		int32 particleIndex = FCString::Atoi(*indexString);
		UE_LOG(LogTemp, Warning, TEXT("message received %d"), particleIndex);
		FTransform curr = this->GetTransform();
		SpawnedComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[particleIndex-1],
			ParticlePositions[particleIndex-1]);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *oscPath);
	}
	isSpawned = true;
}

void ANetworkParticleSystem::DeSpawnParticles_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	SpawnedComponent->DestroyComponent();
	isSpawned = false;
}

