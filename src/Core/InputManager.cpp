#include "InputManager.h"
#include <conio.h>

InputManager::InputManager() {
    // 기본 초기화
}

InputManager::~InputManager() {
    // 정리
}

void InputManager::Update() {
    // 이전 프레임 키 상태 저장
    previousKeyState = currentKeyState;
    
    // 현재 키 상태 업데이트
    for (int i = 0; i < 256; ++i) {
        currentKeyState[i] = GetKeyState(i);
    }
}

bool InputManager::IsKeyDown(int keyCode) const {
    auto it = currentKeyState.find(keyCode);
    return (it != currentKeyState.end()) ? it->second : false;
}

bool InputManager::IsKeyPressed(int keyCode) const {
    bool current = IsKeyDown(keyCode);
    auto it = previousKeyState.find(keyCode);
    bool previous = (it != previousKeyState.end()) ? it->second : false;
    
    return current && !previous;
}

bool InputManager::IsKeyReleased(int keyCode) const {
    bool current = IsKeyDown(keyCode);
    auto it = previousKeyState.find(keyCode);
    bool previous = (it != previousKeyState.end()) ? it->second : false;
    
    return !current && previous;
}

bool InputManager::GetKeyState(int keyCode) const {
    // Windows API를 사용한 키 상태 확인
    return (::GetAsyncKeyState(keyCode) & 0x8000) != 0;
} 