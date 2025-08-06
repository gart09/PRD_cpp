#pragma once
#include "Scene.h"

class MenuScene : public Scene {
private:
    bool showRanking;
    
public:
    MenuScene();
    ~MenuScene() override;
    
    void Enter() override;
    void Exit() override;
    void Update(float deltaTime) override;
    void Render() override;
    void HandleInput() override;
    
private:
    void RenderMainMenu();
    void RenderRanking();
    void HandleMenuInput();
    void HandleRankingInput();
}; 