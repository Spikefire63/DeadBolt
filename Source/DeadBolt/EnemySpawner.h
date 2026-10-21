// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyBaseController;

UCLASS()
class DEADBOLT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AEnemyBaseController> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Waves")
	int32 MaxWaves = 3;

	UPROPERTY(EditAnywhere, Category = "Waves")
	int32 EnemiesInFirstWave = 5;

	UPROPERTY(EditAnywhere, Category = "Waves")
	int32 ExtraEnemiesPerWave = 3;

	UPROPERTY(EditAnywhere, Category = "Waves")
	float SpawnInterval = 1.f;

	UPROPERTY(EditAnywhere, Category = "Waves")
	float TimeBetweenWaves = 5.f;

private:
	FTimerHandle SpawnTimer;
	FTimerHandle WaveTimer;

	int32 CurrentWave = 0;
	int32 EnemiesToSpawn = 0; 
	int32 EnemiesAlive = 0;    

	void StartNextWave();
	void SpawnEnemy();

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
};
