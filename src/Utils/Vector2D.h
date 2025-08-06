#pragma once

class Vector2D {
public:
    float x, y;
    
    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    
    // 연산자 오버로딩
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    bool operator==(const Vector2D& other) const;
    
    // 유틸리티 함수
    float Distance(const Vector2D& other) const;
    float Length() const;
    Vector2D Normalize() const;
    
    // 정적 함수
    static Vector2D Zero() { return Vector2D(0.0f, 0.0f); }
    static Vector2D One() { return Vector2D(1.0f, 1.0f); }
}; 