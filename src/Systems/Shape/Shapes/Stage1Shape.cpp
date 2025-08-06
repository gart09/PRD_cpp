#include "Stage1Shape.h"
#include "../../Wave/Enemies/EnemyBase.h"
#include <iostream>
#include <chrono>

Stage1Shape::Stage1Shape(ShapeType type, Vector2D gridPos) 
    : ShapeBase(type, 1, gridPos) {
    // 1단계 도형 초기화
}

void Stage1Shape::Update(float deltaTime) {
    // 1단계 도형은 기본적인 업데이트만 수행
    // 공격 쿨다운 등 처리
}

void Stage1Shape::Attack(EnemyBase* target) {
    if (!CanAttack() || target == nullptr) {
        return;
    }
    
    // 기본 공격 수행
    std::cout << GetDisplayName() << "이(가) 공격! 데미지: " << attackPower << std::endl;
    
    // 공격 시간 업데이트
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    lastAttackTime = duration.count() / 1000.0f;
}

void Stage1Shape::Render() {
    // 콘솔 기반 렌더링 (임시)
    // 실제로는 그래픽 라이브러리 사용
}

std::string Stage1Shape::GetDisplayName() const {
    switch (type) {
        case ShapeType::SQUARE: return "네모";
        case ShapeType::TRIANGLE: return "세모";
        case ShapeType::CIRCLE: return "동그라미";
        case ShapeType::LINE: return "직선";
        default: return "도형";
    }
} 