#pragma once
#include "ShapeBase.h"

// 1단계 도형 클래스
class Stage1Shape : public ShapeBase {
public:
    Stage1Shape(ShapeType type, Vector2D gridPos);
    ~Stage1Shape() override = default;
    
    void Update(float deltaTime) override;
    void Attack(EnemyBase* target) override;
    void Render() override;
    
    std::string GetDisplayName() const override;
};

// 구체적인 1단계 도형들
class SquareShape : public Stage1Shape {
public:
    SquareShape(Vector2D gridPos) : Stage1Shape(ShapeType::SQUARE, gridPos) {}
    std::string GetDisplayName() const override { return "네모"; }
};

class TriangleShape : public Stage1Shape {
public:
    TriangleShape(Vector2D gridPos) : Stage1Shape(ShapeType::TRIANGLE, gridPos) {}
    std::string GetDisplayName() const override { return "세모"; }
};

class CircleShape : public Stage1Shape {
public:
    CircleShape(Vector2D gridPos) : Stage1Shape(ShapeType::CIRCLE, gridPos) {}
    std::string GetDisplayName() const override { return "동그라미"; }
};

class LineShape : public Stage1Shape {
public:
    LineShape(Vector2D gridPos) : Stage1Shape(ShapeType::LINE, gridPos) {}
    std::string GetDisplayName() const override { return "직선"; }
}; 