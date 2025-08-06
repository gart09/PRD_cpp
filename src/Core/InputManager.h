#pragma once
#include <unordered_map>
#include <windows.h>

class InputManager {
private:
    std::unordered_map<int, bool> currentKeyState;
    std::unordered_map<int, bool> previousKeyState;
    
public:
    InputManager();
    ~InputManager();
    
    void Update();
    
    // 키 상태 확인
    bool IsKeyDown(int keyCode) const;        // 키가 눌려있는 동안
    bool IsKeyPressed(int keyCode) const;     // 키가 방금 눌림
    bool IsKeyReleased(int keyCode) const;    // 키가 방금 뗌
    
private:
    bool GetKeyState(int keyCode) const;
}; 