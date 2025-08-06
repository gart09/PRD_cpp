#pragma once
#include <unordered_map>
#include <string>

// 간단한 텍스처 클래스 (임시)
class Texture {
public:
    std::string path;
    int width, height;
    
    Texture(const std::string& path) : path(path), width(64), height(64) {}
};

// 간단한 사운드 클래스 (임시)
class Sound {
public:
    std::string path;
    
    Sound(const std::string& path) : path(path) {}
    void Play() { /* 임시 구현 */ }
};

class ResourceManager {
private:
    static ResourceManager* instance;
    
    std::unordered_map<std::string, Texture*> textures;
    std::unordered_map<std::string, Sound*> sounds;
    
    // 생성자를 private로 만들어 싱글톤 패턴 구현
    ResourceManager();
    
public:
    ~ResourceManager();
    
    // 싱글톤 인스턴스 반환
    static ResourceManager* GetInstance();
    static void DestroyInstance();
    
    // 초기화
    bool Initialize();
    
    // 텍스처 관리
    Texture* LoadTexture(const std::string& name, const std::string& path);
    Texture* GetTexture(const std::string& name);
    void UnloadTexture(const std::string& name);
    
    // 사운드 관리
    Sound* LoadSound(const std::string& name, const std::string& path);
    Sound* GetSound(const std::string& name);
    void UnloadSound(const std::string& name);
    
    // 모든 리소스 해제
    void UnloadAllResources();
}; 