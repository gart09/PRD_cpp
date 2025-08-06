#include "WaveManager.h"
#include "Enemies/EnemyBase.h"
#include "../Economy/CurrencyManager.h"
#include <iostream>

WaveManager::WaveManager() 
    : currentWave(0), enemiesRemaining(0), spawnTimer(0.0f), 
      spawnInterval(0.5f), waveActive(false) {
    // 기본 초기화
}

WaveManager::~WaveManager() {
    activeEnemies.clear();
}

void WaveManager::Update(float deltaTime) {
    if (!waveActive) {
        return;
    }
    
    // 스폰 타이머 업데이트
    spawnTimer += deltaTime;
    
    // 적 스폰
    if (spawnTimer >= spawnInterval && enemiesRemaining > 0) {
        SpawnEnemy();
        spawnTimer = 0.0f;
        enemiesRemaining--;
    }
    
    // 활성 적들 업데이트
    for (auto& enemy : activeEnemies) {
        if (enemy) {
            enemy->Update(deltaTime);
        }
    }
    
    // 죽은 적들 제거
    activeEnemies.erase(
        std::remove_if(activeEnemies.begin(), activeEnemies.end(),
            [](const std::unique_ptr<EnemyBase>& enemy) {
                return enemy == nullptr || enemy->IsDead();
            }),
        activeEnemies.end());
}

void WaveManager::StartWave(int waveNumber) {
    currentWave = waveNumber;
    InitializeWave(waveNumber);
    waveActive = true;
    spawnTimer = 0.0f;
    
    std::cout << "웨이브 " << currentWave << " 시작!" << std::endl;
}

bool WaveManager::IsWaveComplete() const {
    return waveActive && enemiesRemaining == 0 && activeEnemies.empty();
}

void WaveManager::SpawnEnemy() {
    // 임시 구현 - 실제로는 EnemyFactory를 사용해야 함
    std::cout << "적 스폰! (임시 메시지)" << std::endl;
    
    // 임시로 적 생성하지 않고 카운트만 감소
    // 실제 구현 시에는 EnemyFactory::CreateEnemy() 사용
}

void WaveManager::RemoveEnemy(EnemyBase* enemy) {
    activeEnemies.erase(
        std::remove_if(activeEnemies.begin(), activeEnemies.end(),
            [enemy](const std::unique_ptr<EnemyBase>& ptr) {
                return ptr.get() == enemy;
            }),
        activeEnemies.end());
}

void WaveManager::InitializeWave(int waveNumber) {
    if (ShouldSpawnBoss(waveNumber)) {
        // 보스 웨이브
        enemiesRemaining = 1;
        std::cout << "보스 웨이브!" << std::endl;
    } else {
        // 일반 웨이브
        enemiesRemaining = 30;
        std::cout << "일반 웨이브 - 적 30마리" << std::endl;
    }
}

bool WaveManager::ShouldSpawnBoss(int waveNumber) const {
    return (waveNumber % 10) == 0;  // 10의 배수 웨이브에서 보스 등장
} 