#include "Vector2D.h"
#include <cmath>

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

bool Vector2D::operator==(const Vector2D& other) const {
    return (abs(x - other.x) < 0.001f) && (abs(y - other.y) < 0.001f);
}

float Vector2D::Distance(const Vector2D& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}

float Vector2D::Length() const {
    return sqrt(x * x + y * y);
}

Vector2D Vector2D::Normalize() const {
    float length = Length();
    if (length > 0.0f) {
        return Vector2D(x / length, y / length);
    }
    return Vector2D::Zero();
} 