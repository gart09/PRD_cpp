#include "ShapeFactory.h"
#include "Shapes/Stage1Shape.h"
#include <random>
#include <ctime>

std::unique_ptr<ShapeBase> ShapeFactory::CreateShape(ShapeType type, Vector2D gridPos) {
    switch (type) {
        case ShapeType::SQUARE:
            return std::make_unique<SquareShape>(gridPos);
        case ShapeType::TRIANGLE:
            return std::make_unique<TriangleShape>(gridPos);
        case ShapeType::CIRCLE:
            return std::make_unique<CircleShape>(gridPos);
        case ShapeType::LINE:
            return std::make_unique<LineShape>(gridPos);
        // 2단계 도형들은 나중에 구현
        default:
            return std::make_unique<SquareShape>(gridPos);  // 기본값
    }
}

std::unique_ptr<ShapeBase> ShapeFactory::CreateRandomShape(int stage, Vector2D gridPos) {
    switch (stage) {
        case 1:
            return CreateRandomStage1Shape(gridPos);
        case 2:
            return CreateRandomStage2Shape(gridPos);
        default:
            return CreateRandomStage1Shape(gridPos);
    }
}

std::unique_ptr<ShapeBase> ShapeFactory::CreateRandomStage1Shape(Vector2D gridPos) {
    ShapeType randomType = GetRandomStage1Type();
    return CreateShape(randomType, gridPos);
}

std::unique_ptr<ShapeBase> ShapeFactory::CreateRandomStage2Shape(Vector2D gridPos) {
    // 임시로 1단계 도형 반환 (2단계 구현 전까지)
    return CreateRandomStage1Shape(gridPos);
}

ShapeType ShapeFactory::GetRandomStage1Type() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 3);
    
    ShapeType types[] = {
        ShapeType::SQUARE,
        ShapeType::TRIANGLE,
        ShapeType::CIRCLE,
        ShapeType::LINE
    };
    
    return types[dis(gen)];
}

ShapeType ShapeFactory::GetRandomStage2Type() {
    // 임시로 1단계 타입 반환
    return GetRandomStage1Type();
} 