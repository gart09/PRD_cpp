#pragma once
#include "Scene.h"
#include <memory>

class ShapeManager;
class WaveManager;
class CurrencyManager;

class GameScene : public Scene {
private:
    std::unique_ptr<ShapeManager> shapeManager;
    std::unique_ptr<WaveManager> waveManager;
    
    float gameTime;
    int currentWave;
    bool isPaused;
    
public:
    GameScene();
    ~GameScene() override;
    
    void Enter() override;
    void Exit() override;
    void Update(float deltaTime) override;
    void Render() override;
    void HandleInput() override;
    
private:
    void RenderUI();
    void RenderGrid();
    void RenderWaveInfo();
    void HandleGameInput();
    void HandlePauseInput();
}; 