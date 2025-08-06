#pragma once
#include <memory>

class SceneManager;
class ResourceManager;
class InputManager;
class CurrencyManager;

class Game {
private:
    static Game* instance;
    
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<InputManager> inputManager;
    
    bool isRunning;
    float deltaTime;
    
    // 생성자를 private로 만들어 싱글톤 패턴 구현
    Game();
    
public:
    ~Game();
    
    // 싱글톤 인스턴스 반환
    static Game* GetInstance();
    static void DestroyInstance();
    
    // 게임 라이프사이클
    bool Initialize();
    void Run();
    void Update(float deltaTime);
    void Render();
    void Cleanup();
    
    // 유틸리티
    bool IsRunning() const { return isRunning; }
    void Quit() { isRunning = false; }
    float GetDeltaTime() const { return deltaTime; }
    
    // 매니저 접근자
    SceneManager* GetSceneManager() const { return sceneManager.get(); }
    InputManager* GetInputManager() const { return inputManager.get(); }
}; 