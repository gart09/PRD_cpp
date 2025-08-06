#pragma once
#include <memory>

class Scene;

class SceneManager {
private:
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<Scene> nextScene;
    
public:
    SceneManager();
    ~SceneManager();
    
    void ChangeScene(std::unique_ptr<Scene> newScene);
    void Update(float deltaTime);
    void Render();
    
    Scene* GetCurrentScene() const { return currentScene.get(); }
}; 