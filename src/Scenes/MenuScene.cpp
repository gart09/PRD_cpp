#include "MenuScene.h"
#include "GameScene.h"
#include "../Core/Game.h"
#include "../Core/SceneManager.h"
#include "../Core/InputManager.h"
#include <iostream>

MenuScene::MenuScene() : showRanking(false) {
    // 기본 초기화
}

MenuScene::~MenuScene() {
    // 정리
}

void MenuScene::Enter() {
    std::cout << "메뉴 씬 진입" << std::endl;
    showRanking = false;
}

void MenuScene::Exit() {
    std::cout << "메뉴 씬 종료" << std::endl;
}

void MenuScene::Update(float deltaTime) {
    HandleInput();
}

void MenuScene::Render() {
    if (showRanking) {
        RenderRanking();
    } else {
        RenderMainMenu();
    }
}

void MenuScene::HandleInput() {
    if (showRanking) {
        HandleRankingInput();
    } else {
        HandleMenuInput();
    }
}

void MenuScene::RenderMainMenu() {
    // 콘솔 기반 임시 UI
    system("cls"); // Windows용 화면 클리어
    
    std::cout << "======================================" << std::endl;
    std::cout << "        랜덤 디펜스 게임" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << std::endl;
    std::cout << "1. 게임 시작" << std::endl;
    std::cout << "2. 랭킹 보기" << std::endl;
    std::cout << "3. 게임 종료" << std::endl;
    std::cout << std::endl;
    std::cout << "선택: ";
}

void MenuScene::RenderRanking() {
    system("cls");
    
    std::cout << "======================================" << std::endl;
    std::cout << "            랭킹" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Player1 - 15:30" << std::endl;
    std::cout << "2. Player2 - 18:45" << std::endl;
    std::cout << "3. Player3 - 22:10" << std::endl;
    std::cout << std::endl;
    std::cout << "ESC. Back" << std::endl;
}

void MenuScene::HandleMenuInput() {
    InputManager* input = Game::GetInstance()->GetInputManager();
    
    // 임시 키보드 입력 처리
    if (input->IsKeyPressed('1')) {
        // 게임 시작
        Game::GetInstance()->GetSceneManager()->ChangeScene(std::make_unique<GameScene>());
    }
    else if (input->IsKeyPressed('2')) {
        // 랭킹 보기
        showRanking = true;
    }
    else if (input->IsKeyPressed('3')) {
        // 게임 종료
        Game::GetInstance()->Quit();
    }
}

void MenuScene::HandleRankingInput() {
    InputManager* input = Game::GetInstance()->GetInputManager();
    
    if (input->IsKeyPressed(27)) { // ESC
        showRanking = false;
    }
} 