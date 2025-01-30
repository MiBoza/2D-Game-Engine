#include "Vector2.hpp"

float Ipow(float x, int y){
    float result = x;
    if(y == 0)
        return x;
    if(x == 0)
        return 0;
    if(y < 0)
        return 1/Ipow(x, -y);
    for(int i = 1; i < y; i++)
        result *= x;

    return result;
}

float Magnitude_Squared(const Vector2& u){
    return Ipow(u.x, 2) + Ipow(u.y, 2);
}

float Magnitude(const Vector2& u){
    return sqrt( Magnitude_Squared(u) );
}

Vector2 operator-(const Vector2& u, const Vector2& v){
    Vector2 result = {u.x - v.x, u.y - v.y};
    return result;
}

Vector2 operator+(const Vector2& u, const Vector2& v){
    Vector2 result = {u.x + v.x, u.y + v.y};
    return result;
}

Vector2 operator*(const Vector2& u, const Vector2& v){
    Vector2 result = {u.x*v.x, u.y*v.y};
    return result;
}

Vector2 operator/(const Vector2& u, float A){
    Vector2 result = {u.x/A, u.y/A};
    return result;
}

bool Not_Zero(const Vector2& u){
    if(u.x || u.y)
        return 1;
    else
        return 0;
}

void operator+=(Vector2& u, const Vector2& v){
    u.x += v.x;
    u.y += v.y;
}

void operator*=(Vector2& u, float A){
    u.x *= A;
    u.y *= A;
}

Vector2 operator*(const Vector2& u, float A){
    Vector2 result = {A*u.x, A*u.y};
    return result;
}

Vector2 operator*(float A, const Vector2& u){
    Vector2 result = {A*u.x, A*u.y};
    return result;
}

void Print_Vector2(const Vector2& u){
    printf("[%.2f, %.2f]\n", u.x, u.y);
}
