#pragma once
#include "../../../Utils/Vector2D.h"
#include <string>

// 도형 타입 열거형
enum class ShapeType {
    // 1단계
    SQUARE, TRIANGLE, CIRCLE, LINE,
    
    // 2단계 - 머리
    DOG_HEAD, CAT_HEAD, BIRD_HEAD, CAPYBARA_HEAD,
    
    // 2단계 - 몸통
    FAT_BODY, THIN_BODY, NORMAL_BODY,
    
    // 2단계 - 꼬리
    POWER_TAIL, RAGE_TAIL, NORMAL_TAIL,
    
    // 3단계 (조합)
    STAGE3_COMBINED
};

// 2단계 도형의 부위 타입
enum class PartType {
    HEAD, BODY, TAIL
};

// 전방 선언
class EnemyBase;

class ShapeBase {
protected:
    ShapeType type;
    int stage;
    Vector2D position;
    Vector2D gridPosition;  // 4x4 격자에서의 위치
    
    // 능력치
    float attackPower;
    float attackSpeed;
    float lastAttackTime;
    
    // 스킬 관련
    int skillUseCount;      // 스킬 사용 횟수 (n번 공격 시)
    
public:
    ShapeBase(ShapeType type, int stage, Vector2D gridPos);
    virtual ~ShapeBase() = default;
    
    // 가상 함수들
    virtual void Update(float deltaTime) = 0;
    virtual void Attack(EnemyBase* target) = 0;
    virtual void UseSkill() {}  // 2단계부터 구현
    virtual void Render() = 0;
    
    // 접근자
    ShapeType GetType() const { return type; }
    int GetStage() const { return stage; }
    Vector2D GetPosition() const { return position; }
    Vector2D GetGridPosition() const { return gridPosition; }
    float GetAttackPower() const { return attackPower; }
    float GetAttackSpeed() const { return attackSpeed; }
    
    // 설정자
    void SetPosition(const Vector2D& pos) { position = pos; }
    void SetGridPosition(const Vector2D& gridPos) { gridPosition = gridPos; }
    void SetAttackPower(float power) { attackPower = power; }
    void SetAttackSpeed(float speed) { attackSpeed = speed; }
    
    // 유틸리티
    bool CanAttack() const;
    virtual std::string GetDisplayName() const = 0;
    virtual int GetSellPrice() const;
}; 