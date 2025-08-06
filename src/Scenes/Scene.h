#pragma once

// 씬 기본 클래스 (상태 패턴)
class Scene {
public:
    virtual ~Scene() = default;
    
    virtual void Enter() = 0;     // 씬 진입 시
    virtual void Exit() = 0;      // 씬 종료 시
    virtual void Update(float deltaTime) = 0;  // 프레임마다 업데이트
    virtual void Render() = 0;    // 렌더링
    virtual void HandleInput() = 0;  // 입력 처리
}; 