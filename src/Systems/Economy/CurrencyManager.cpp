#include "CurrencyManager.h"
#include <iostream>

CurrencyManager* CurrencyManager::instance = nullptr;

CurrencyManager::CurrencyManager() : currentCurrency(100) {
    // 초기 재화 100으로 시작
}

CurrencyManager::~CurrencyManager() {
    // 정리
}

CurrencyManager* CurrencyManager::GetInstance() {
    if (instance == nullptr) {
        instance = new CurrencyManager();
    }
    return instance;
}

void CurrencyManager::DestroyInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

void CurrencyManager::Initialize() {
    currentCurrency = 100;  // 게임 시작 시 초기 재화
    std::cout << "CurrencyManager 초기화 - 초기 재화: " << currentCurrency << std::endl;
}

bool CurrencyManager::CanAfford(int cost) const {
    return currentCurrency >= cost;
}

bool CurrencyManager::SpendCurrency(int amount) {
    if (CanAfford(amount)) {
        currentCurrency -= amount;
        std::cout << "재화 소모: -" << amount << " (잔액: " << currentCurrency << ")" << std::endl;
        return true;
    } else {
        std::cout << "재화 부족! 필요: " << amount << ", 보유: " << currentCurrency << std::endl;
        return false;
    }
}

void CurrencyManager::AddCurrency(int amount) {
    currentCurrency += amount;
    std::cout << "재화 획득: +" << amount << " (잔액: " << currentCurrency << ")" << std::endl;
}

int CurrencyManager::GetShapePrice(int stage) const {
    switch (stage) {
        case 1: return 10;
        case 2: return 30;
        case 3: return 90;
        default: return 10;
    }
} 