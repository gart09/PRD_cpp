#include "ShapeManager.h"
#include "ShapeFactory.h"
#include "Shapes/ShapeBase.h"
#include "../Economy/CurrencyManager.h"
#include <iostream>
#include <algorithm>

ShapeManager::ShapeManager() {
    InitializeGrid();
}

ShapeManager::~ShapeManager() {
    shapes.clear();
}

void ShapeManager::InitializeGrid() {
    // 격자 초기화
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            grid[y][x] = nullptr;
        }
    }
}

void ShapeManager::Update(float deltaTime) {
    // 모든 도형 업데이트
    for (auto& shape : shapes) {
        if (shape) {
            shape->Update(deltaTime);
        }
    }
    
    // 합성 가능 여부 확인
    CheckSynthesis();
}

void ShapeManager::RenderGrid() {
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (grid[y][x] != nullptr) {
                // 도형이 있는 경우 첫 글자 표시
                std::string name = grid[y][x]->GetDisplayName();
                std::cout << "[" << (name.empty() ? "?" : name.substr(0, 2)) << "] ";
            } else {
                std::cout << "[ ] ";
            }
        }
        std::cout << std::endl;
    }
}

bool ShapeManager::PurchaseShape(int stage) {
    CurrencyManager* currency = CurrencyManager::GetInstance();
    int price = currency->GetShapePrice(stage);
    
    if (!currency->CanAfford(price)) {
        return false;
    }
    
    // 빈 공간 찾기
    Vector2D emptyPos = FindEmptyPosition();
    if (emptyPos.x == -1 || emptyPos.y == -1) {
        std::cout << "격자가 가득참! 도형을 배치할 수 없습니다." << std::endl;
        return false;
    }
    
    // 재화 차감
    if (currency->SpendCurrency(price)) {
        // 도형 생성 (팩토리 패턴)
        std::unique_ptr<ShapeBase> newShape = ShapeFactory::CreateRandomShape(stage, emptyPos);
        
        if (newShape) {
            // 격자에 배치
            PlaceShapeOnGrid(newShape.get(), static_cast<int>(emptyPos.x), static_cast<int>(emptyPos.y));
            
            // 관리 목록에 추가
            shapes.push_back(std::move(newShape));
            
            std::cout << "도형 구매 성공! 위치: (" << emptyPos.x << ", " << emptyPos.y << ")" << std::endl;
            return true;
        }
    }
    
    return false;
}

void ShapeManager::SellShape(int gridX, int gridY) {
    if (gridX < 0 || gridX >= 4 || gridY < 0 || gridY >= 4) {
        return;
    }
    
    ShapeBase* shape = grid[gridY][gridX];
    if (shape == nullptr) {
        return;
    }
    
    // 판매 가격 계산 (80%)
    int sellPrice = shape->GetSellPrice();
    CurrencyManager::GetInstance()->AddCurrency(sellPrice);
    
    // 격자에서 제거
    RemoveShapeFromGrid(gridX, gridY);
    
    // 관리 목록에서 제거
    auto it = std::find_if(shapes.begin(), shapes.end(),
        [shape](const std::unique_ptr<ShapeBase>& ptr) {
            return ptr.get() == shape;
        });
    if (it != shapes.end()) {
        shapes.erase(it);
    }
    
    std::cout << "도형 판매 완료! 획득 재화: " << sellPrice << std::endl;
}

void ShapeManager::MoveShape(int fromX, int fromY, int toX, int toY) {
    if (fromX < 0 || fromX >= 4 || fromY < 0 || fromY >= 4 ||
        toX < 0 || toX >= 4 || toY < 0 || toY >= 4) {
        return;
    }
    
    ShapeBase* shape = grid[fromY][fromX];
    if (shape == nullptr || grid[toY][toX] != nullptr) {
        return;  // 시작 위치에 도형이 없거나 목표 위치에 도형이 있음
    }
    
    // 이동
    grid[fromY][fromX] = nullptr;
    grid[toY][toX] = shape;
    shape->SetGridPosition(Vector2D(static_cast<float>(toX), static_cast<float>(toY)));
    
    std::cout << "도형 이동: (" << fromX << "," << fromY << ") -> (" << toX << "," << toY << ")" << std::endl;
}

bool ShapeManager::IsGridEmpty(int x, int y) const {
    if (x < 0 || x >= 4 || y < 0 || y >= 4) {
        return false;
    }
    return grid[y][x] == nullptr;
}

Vector2D ShapeManager::FindEmptyPosition() const {
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (IsGridEmpty(x, y)) {
                return Vector2D(static_cast<float>(x), static_cast<float>(y));
            }
        }
    }
    return Vector2D(-1, -1);  // 빈 공간 없음
}

void ShapeManager::PlaceShapeOnGrid(ShapeBase* shape, int x, int y) {
    if (x >= 0 && x < 4 && y >= 0 && y < 4 && grid[y][x] == nullptr) {
        grid[y][x] = shape;
        shape->SetGridPosition(Vector2D(static_cast<float>(x), static_cast<float>(y)));
    }
}

void ShapeManager::RemoveShapeFromGrid(int x, int y) {
    if (x >= 0 && x < 4 && y >= 0 && y < 4) {
        grid[y][x] = nullptr;
    }
}

void ShapeManager::CheckSynthesis() {
    // 임시 구현 - 실제로는 복잡한 패턴 매칭 로직이 필요
    // 현재는 스텁으로만 구현
} 