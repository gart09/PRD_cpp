#include "ShapeBase.h"
#include <chrono>

ShapeBase::ShapeBase(ShapeType type, int stage, Vector2D gridPos) 
    : type(type), stage(stage), gridPosition(gridPos), position(gridPos), 
      attackPower(10.0f), attackSpeed(1.0f), lastAttackTime(0.0f), skillUseCount(0) {
    
    // 단계별 기본 능력치 설정
    switch (stage) {
        case 1:
            attackPower = 10.0f;
            attackSpeed = 1.0f;
            break;
        case 2:
            attackPower = 25.0f;
            attackSpeed = 1.2f;
            break;
        case 3:
            attackPower = 60.0f;
            attackSpeed = 1.5f;
            break;
        default:
            attackPower = 10.0f;
            attackSpeed = 1.0f;
            break;
    }
}

bool ShapeBase::CanAttack() const {
    // 현재 시간 가져오기
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    float currentTime = duration.count() / 1000.0f;
    
    // 공격 쿨다운 확인
    float cooldown = 1.0f / attackSpeed;  // 공격속도의 역수가 쿨다운
    return (currentTime - lastAttackTime) >= cooldown;
}

int ShapeBase::GetSellPrice() const {
    // 단계별 기본 가격의 80%
    int basePrice = 0;
    switch (stage) {
        case 1: basePrice = 10; break;
        case 2: basePrice = 30; break;
        case 3: basePrice = 90; break;
        default: basePrice = 10; break;
    }
    return static_cast<int>(basePrice * 0.8f);
} 