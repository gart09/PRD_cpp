#include "ResourceManager.h"
#include <iostream>

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager() {
    // 기본 초기화
}

ResourceManager::~ResourceManager() {
    UnloadAllResources();
}

ResourceManager* ResourceManager::GetInstance() {
    if (instance == nullptr) {
        instance = new ResourceManager();
    }
    return instance;
}

void ResourceManager::DestroyInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

bool ResourceManager::Initialize() {
    std::cout << "ResourceManager Initialize" << std::endl;
    
    // 기본 리소스들 로드
    LoadTexture("square", "assets/images/square.png");
    LoadTexture("triangle", "assets/images/triangle.png");
    LoadTexture("circle", "assets/images/circle.png");
    LoadTexture("line", "assets/images/line.png");
    
    LoadSound("click", "assets/sounds/click.wav");
    LoadSound("synthesis", "assets/sounds/synthesis.wav");
    
    return true;
}

Texture* ResourceManager::LoadTexture(const std::string& name, const std::string& path) {
    // 이미 로드된 텍스처인지 확인
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    
    // 새 텍스처 생성 (실제로는 파일을 로드해야 함)
    Texture* texture = new Texture(path);
    textures[name] = texture;
    
    std::cout << "텍스처 로드: " << name << " (" << path << ")" << std::endl;
    return texture;
}

Texture* ResourceManager::GetTexture(const std::string& name) {
    auto it = textures.find(name);
    return (it != textures.end()) ? it->second : nullptr;
}

void ResourceManager::UnloadTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        delete it->second;
        textures.erase(it);
        std::cout << "텍스처 언로드: " << name << std::endl;
    }
}

Sound* ResourceManager::LoadSound(const std::string& name, const std::string& path) {
    // 이미 로드된 사운드인지 확인
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        return it->second;
    }
    
    // 새 사운드 생성
    Sound* sound = new Sound(path);
    sounds[name] = sound;
    
    std::cout << "사운드 로드: " << name << " (" << path << ")" << std::endl;
    return sound;
}

Sound* ResourceManager::GetSound(const std::string& name) {
    auto it = sounds.find(name);
    return (it != sounds.end()) ? it->second : nullptr;
}

void ResourceManager::UnloadSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        delete it->second;
        sounds.erase(it);
        std::cout << "사운드 언로드: " << name << std::endl;
    }
}

void ResourceManager::UnloadAllResources() {
    // 모든 텍스처 해제
    for (auto& pair : textures) {
        delete pair.second;
    }
    textures.clear();
    
    // 모든 사운드 해제
    for (auto& pair : sounds) {
        delete pair.second;
    }
    sounds.clear();
    
    std::cout << "모든 리소스 언로드 완료" << std::endl;
} 