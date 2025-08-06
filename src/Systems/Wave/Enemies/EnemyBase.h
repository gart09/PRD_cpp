#pragma once
#include "../../../Utils/Vector2D.h"

class EnemyBase {
protected:
    Vector2D position;
    float health;
    float maxHealth;
    float moveSpeed;
    bool isDead;
    
public:
    EnemyBase(float health, float moveSpeed);
    virtual ~EnemyBase() = default;
    
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void TakeDamage(float damage);
    
    // 접근자
    bool IsDead() const { return isDead; }
    float GetHealth() const { return health; }
    float GetMaxHealth() const { return maxHealth; }
    Vector2D GetPosition() const { return position; }
    
    // 설정자
    void SetPosition(const Vector2D& pos) { position = pos; }
}; 