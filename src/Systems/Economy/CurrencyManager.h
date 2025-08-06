#pragma once

class CurrencyManager {
private:
    static CurrencyManager* instance;
    
    int currentCurrency;
    
    // 생성자를 private로 만들어 싱글톤 패턴 구현
    CurrencyManager();
    
public:
    ~CurrencyManager();
    
    // 싱글톤 인스턴스 반환
    static CurrencyManager* GetInstance();
    static void DestroyInstance();
    
    // 초기화
    void Initialize();
    
    // 재화 관리
    bool CanAfford(int cost) const;
    bool SpendCurrency(int amount);
    void AddCurrency(int amount);
    int GetCurrency() const { return currentCurrency; }
    
    // 도형 가격 계산
    int GetShapePrice(int stage) const;
}; 