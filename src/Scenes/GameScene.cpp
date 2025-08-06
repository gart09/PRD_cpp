#include "GameScene.h"
#include "MenuScene.h"
#include "../Core/Game.h"
#include "../Core/SceneManager.h"
#include "../Core/InputManager.h"
#include "../Systems/Shape/ShapeManager.h"
#include "../Systems/Wave/WaveManager.h"
#include "../Systems/Economy/CurrencyManager.h"
#include <iostream>

GameScene::GameScene() : gameTime(0.0f), currentWave(1), isPaused(false) {
    // 기본 초기화
}

GameScene::~GameScene() {
    // 정리
}

void GameScene::Enter() {
    std::cout << "게임 씬 진입" << std::endl;
    
    // 매니저들 초기화
    shapeManager = std::make_unique<ShapeManager>();
    waveManager = std::make_unique<WaveManager>();
    
    // 게임 초기화
    gameTime = 0.0f;
    currentWave = 1;
    isPaused = false;
    
    // 첫 번째 웨이브 시작
    waveManager->StartWave(currentWave);
}

void GameScene::Exit() {
    std::cout << "게임 씬 종료" << std::endl;
    
    shapeManager.reset();
    waveManager.reset();
}

void GameScene::Update(float deltaTime) {
    if (!isPaused) {
        gameTime += deltaTime;
        
        // 매니저들 업데이트
        if (shapeManager) {
            shapeManager->Update(deltaTime);
        }
        
        if (waveManager) {
            waveManager->Update(deltaTime);
            
            // 웨이브 완료 확인
            if (waveManager->IsWaveComplete()) {
                currentWave++;
                if (currentWave <= 30) {
                    waveManager->StartWave(currentWave);
                } else {
                    // 게임 클리어
                    std::cout << "게임 클리어!" << std::endl;
                    Game::GetInstance()->GetSceneManager()->ChangeScene(std::make_unique<MenuScene>());
                    return;
                }
            }
        }
    }
    
    HandleInput();
}

void GameScene::Render() {
    // 화면 클리어
    system("cls");
    
    if (isPaused) {
        std::cout << "=== GAME PAUSED ===" << std::endl;
        std::cout << "R: Resume, M: Back to Menu" << std::endl;
        return;
    }
    
    RenderUI();
    RenderGrid();
    RenderWaveInfo();
}

void GameScene::HandleInput() {
    if (isPaused) {
        HandlePauseInput();
    } else {
        HandleGameInput();
    }
}

void GameScene::RenderUI() {
    CurrencyManager* currency = CurrencyManager::GetInstance();
    
    std::cout << "=== 랜덤 디펜스 게임 ===" << std::endl;
    std::cout << "시간: " << static_cast<int>(gameTime) << "초 | ";
    std::cout << "웨이브: " << currentWave << "/30 | ";
    std::cout << "재화: " << currency->GetCurrency() << std::endl;
    std::cout << "==============================" << std::endl;
}

void GameScene::RenderGrid() {
    std::cout << "\n[4x4 격자판]" << std::endl;
    
    if (shapeManager) {
        shapeManager->RenderGrid();
    } else {
        // 임시 격자 표시
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                std::cout << "[ ] ";
            }
            std::cout << std::endl;
        }
    }
}

void GameScene::RenderWaveInfo() {
    std::cout << "\n[Controls]" << std::endl;
    std::cout << "1: Stage1 Shape(10G) | 2: Stage2 Shape(30G)" << std::endl;
    std::cout << "P: Pause | ESC: Back to Menu" << std::endl;
}

void GameScene::HandleGameInput() {
    InputManager* input = Game::GetInstance()->GetInputManager();
    
    if (input->IsKeyPressed('1')) {
        // 1단계 도형 뽑기
        if (shapeManager) {
            shapeManager->PurchaseShape(1);
        }
    }
    else if (input->IsKeyPressed('2')) {
        // 2단계 도형 뽑기
        if (shapeManager) {
            shapeManager->PurchaseShape(2);
        }
    }
    else if (input->IsKeyPressed('P') || input->IsKeyPressed('p')) {
        // 일시정지
        isPaused = true;
    }
    else if (input->IsKeyPressed(27)) { // ESC
        // 메뉴로 돌아가기
        Game::GetInstance()->GetSceneManager()->ChangeScene(std::make_unique<MenuScene>());
    }
}

void GameScene::HandlePauseInput() {
    InputManager* input = Game::GetInstance()->GetInputManager();
    
    if (input->IsKeyPressed('R') || input->IsKeyPressed('r')) {
        // 재개
        isPaused = false;
    }
    else if (input->IsKeyPressed('M') || input->IsKeyPressed('m')) {
        // 메뉴로 돌아가기
        Game::GetInstance()->GetSceneManager()->ChangeScene(std::make_unique<MenuScene>());
    }
} 