// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NetworkParticleSystem.generated.h"

UCLASS(Blueprintable)
class ARTMULTIPLAYER_API ANetworkParticleSystem : public AActor
{
	GENERATED_BODY()

private:
	bool isSpawned = false;
	UParticleSystemComponent* SpawnedComponent;

public:
	// Sets default values for this actor's properties
	ANetworkParticleSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particles, meta = (AllowPrivateAccess = "true"))
		TArray<UParticleSystem*>  ParticleSystems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particles, meta = (AllowPrivateAccess = "true"))
		TArray<FTransform>  ParticlePositions;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Particles, NetMulticast, Reliable)
		void SpawnParticles(const FString& oscPath);
	void SpawnParticles_Implementation(const FString& oscPath);

	UFUNCTION(BlueprintCallable, Category = Particles, NetMulticast, Reliable)
		void DeSpawnParticles();
	void DeSpawnParticles_Implementation();
};
