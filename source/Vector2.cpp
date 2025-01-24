#include "Vector2.hpp"

Vector2 Vector2::operator-(const Vector2& v){
    Vector2 result = {x - v.x, y - v.y};
    return result;
}

Vector2 Vector2::operator+(const Vector2& v){
    Vector2 result = {x + v.x, y + v.y};
    return result;
}

Vector2 Vector2::operator*(float A){
    Vector2 result = {x*A, y*A};
    return result;
}

Vector2 Vector2::operator/(float A){
    Vector2 result = {x/A, y/A};
    return result;
}

void Vector2::operator+=(const Vector2& v){
    x += v.x;
    y += v.y;
}

void Vector2::operator*=(float A){
    x *= A;
    y *= A;
}

Vector2 operator*(float A, Vector2&& v){
    Vector2 result = {A*v.x, A*v.y};
    return result;
}

void Print_Vector2(const Vector2& v){
    printf("[%.2f, %.2f]\n", v.x, v.y);
}
