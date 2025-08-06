#include "Game.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "../Systems/Economy/CurrencyManager.h"
#include "../Scenes/MenuScene.h"
#include <iostream>
#include <chrono>

Game* Game::instance = nullptr;

Game::Game() : isRunning(false), deltaTime(0.0f) {
    // 기본 초기화
}

Game::~Game() {
    Cleanup();
}

Game* Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::DestroyInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

bool Game::Initialize() {
    std::cout << "게임 초기화 중..." << std::endl;
    
    try {
        // 매니저들 초기화
        sceneManager = std::make_unique<SceneManager>();
        inputManager = std::make_unique<InputManager>();
        
        // 리소스 매니저 초기화 (싱글톤)
        ResourceManager::GetInstance()->Initialize();
        
        // 재화 매니저 초기화 (싱글톤)
        CurrencyManager::GetInstance()->Initialize();
        
        // 메뉴 씬으로 시작
        sceneManager->ChangeScene(std::make_unique<MenuScene>());
        
        isRunning = true;
        std::cout << "게임 초기화 완료!" << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "게임 초기화 실패: " << e.what() << std::endl;
        return false;
    }
}

void Game::Run() {
    if (!Initialize()) {
        return;
    }
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while (isRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        // 입력 처리
        inputManager->Update();
        
        // 게임 업데이트
        Update(deltaTime);
        
        // 렌더링
        Render();
        
        // ESC 키로 종료 (임시)
        if (inputManager->IsKeyPressed(27)) { // ESC key
            Quit();
        }
    }
    
    Cleanup();
}

void Game::Update(float deltaTime) {
    if (sceneManager) {
        sceneManager->Update(deltaTime);
    }
}

void Game::Render() {
    if (sceneManager) {
        sceneManager->Render();
    }
}

void Game::Cleanup() {
    std::cout << "게임 정리 중..." << std::endl;
    
    sceneManager.reset();
    inputManager.reset();
    
    // 싱글톤들 정리
    ResourceManager::DestroyInstance();
    CurrencyManager::DestroyInstance();
    
    std::cout << "게임 정리 완료!" << std::endl;
} 