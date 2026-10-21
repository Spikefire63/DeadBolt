// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyBaseController.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(WaveTimer, this, &AEnemySpawner::StartNextWave, TimeBetweenWaves, false);
	}
}

void AEnemySpawner::StartNextWave()
{
	CurrentWave++;
	EnemiesToSpawn = EnemiesInFirstWave + (CurrentWave - 1) * ExtraEnemiesPerWave;

	UE_LOG(LogTemp, Warning, TEXT("Wave %d starting with %d enemies"), CurrentWave, EnemiesToSpawn);

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true);
}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemiesToSpawn <= 0 || !EnemyClass)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemyBaseController* Enemy = GetWorld()->SpawnActor<AEnemyBaseController>(EnemyClass, GetActorLocation(), GetActorRotation(), Params);
	EnemiesToSpawn--;

	if (Enemy)
	{
		EnemiesAlive++;
		Enemy->OnDestroyed.AddDynamic(this, &AEnemySpawner::OnEnemyDestroyed);
	}
}

void AEnemySpawner::OnEnemyDestroyed(AActor* DestroyedActor)
{
	EnemiesAlive--;
	UE_LOG(LogTemp, Warning, TEXT("Enemies left alive: %d"), EnemiesAlive);

	// Wave is over only when everything is spawned AND everything is dead
	if (EnemiesAlive > 0 || EnemiesToSpawn > 0) return;

	if (CurrentWave >= MaxWaves)
	{
		UE_LOG(LogTemp, Warning, TEXT("All waves cleared!"));
		// later: open the escape here
		return;
	}

	GetWorldTimerManager().SetTimer(WaveTimer, this, &AEnemySpawner::StartNextWave, TimeBetweenWaves, false);
}
