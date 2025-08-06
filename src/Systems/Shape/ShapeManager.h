#pragma once
#include <vector>
#include <memory>
#include "../../Utils/Vector2D.h"

class ShapeBase;

class ShapeManager {
private:
    std::vector<std::unique_ptr<ShapeBase>> shapes;
    ShapeBase* grid[4][4];  // 4x4 격자
    
public:
    ShapeManager();
    ~ShapeManager();
    
    void Update(float deltaTime);
    void RenderGrid();
    
    // 도형 관리
    bool PurchaseShape(int stage);
    void SellShape(int gridX, int gridY);
    void MoveShape(int fromX, int fromY, int toX, int toY);
    
    // 격자 관리
    bool IsGridEmpty(int x, int y) const;
    Vector2D FindEmptyPosition() const;
    void PlaceShapeOnGrid(ShapeBase* shape, int x, int y);
    void RemoveShapeFromGrid(int x, int y);
    
    // 합성 시스템
    void CheckSynthesis();
    
private:
    void InitializeGrid();
}; 