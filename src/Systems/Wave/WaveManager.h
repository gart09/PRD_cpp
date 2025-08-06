#pragma once
#include <vector>
#include <memory>

class EnemyBase;

class WaveManager {
private:
    std::vector<std::unique_ptr<EnemyBase>> activeEnemies;
    int currentWave;
    int enemiesRemaining;
    float spawnTimer;
    float spawnInterval;
    bool waveActive;
    
public:
    WaveManager();
    ~WaveManager();
    
    void Update(float deltaTime);
    void StartWave(int waveNumber);
    bool IsWaveComplete() const;
    
    // 적 관리
    void SpawnEnemy();
    void RemoveEnemy(EnemyBase* enemy);
    
    // 접근자
    int GetCurrentWave() const { return currentWave; }
    int GetEnemiesRemaining() const { return enemiesRemaining; }
    const std::vector<std::unique_ptr<EnemyBase>>& GetActiveEnemies() const { return activeEnemies; }
    
private:
    void InitializeWave(int waveNumber);
    bool ShouldSpawnBoss(int waveNumber) const;
}; 