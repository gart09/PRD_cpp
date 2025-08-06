#include "EnemyBase.h"

EnemyBase::EnemyBase(float health, float moveSpeed) 
    : position(Vector2D::Zero()), health(health), maxHealth(health), 
      moveSpeed(moveSpeed), isDead(false) {
    // 기본 초기화
}

void EnemyBase::TakeDamage(float damage) {
    health -= damage;
    if (health <= 0.0f) {
        health = 0.0f;
        isDead = true;
    }
} 