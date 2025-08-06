#pragma once
#include <memory>
#include "Shapes/ShapeBase.h"
#include "../../Utils/Vector2D.h"

class ShapeFactory {
public:
    // 특정 타입 도형 생성
    static std::unique_ptr<ShapeBase> CreateShape(ShapeType type, Vector2D gridPos);
    
    // 랜덤 도형 생성
    static std::unique_ptr<ShapeBase> CreateRandomShape(int stage, Vector2D gridPos);
    
    // 1단계 랜덤 도형 생성
    static std::unique_ptr<ShapeBase> CreateRandomStage1Shape(Vector2D gridPos);
    
    // 2단계 랜덤 도형 생성
    static std::unique_ptr<ShapeBase> CreateRandomStage2Shape(Vector2D gridPos);
    
private:
    static ShapeType GetRandomStage1Type();
    static ShapeType GetRandomStage2Type();
}; 