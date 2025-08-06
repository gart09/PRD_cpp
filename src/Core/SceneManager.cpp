#include "SceneManager.h"
#include "../Scenes/Scene.h"

SceneManager::SceneManager() {
    // 기본 초기화
}

SceneManager::~SceneManager() {
    currentScene.reset();
    nextScene.reset();
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene) {
    nextScene = std::move(newScene);
}

void SceneManager::Update(float deltaTime) {
    // 씬 전환 처리
    if (nextScene) {
        if (currentScene) {
            currentScene->Exit();
        }
        
        currentScene = std::move(nextScene);
        nextScene.reset();
        
        if (currentScene) {
            currentScene->Enter();
        }
    }
    
    // 현재 씬 업데이트
    if (currentScene) {
        currentScene->Update(deltaTime);
    }
}

void SceneManager::Render() {
    if (currentScene) {
        currentScene->Render();
    }
} 