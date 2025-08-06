#include "Core/Game.h"
#include <iostream>

int main() {
    std::cout << "=== 랜덤 디펜스 게임 시작 ===" << std::endl;
    
    try {
        Game* game = Game::GetInstance();
        game->Run();
        
        Game::DestroyInstance();
    }
    catch (const std::exception& e) {
        std::cerr << "게임 실행 중 오류 발생: " << e.what() << std::endl;
        return -1;
    }
    
    std::cout << "=== 게임 종료 ===" << std::endl;
    return 0;
} 