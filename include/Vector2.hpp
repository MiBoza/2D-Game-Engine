#ifndef Vector2_hpp
#define Vector2_hpp

#include <stdio.h>

struct Vector2{
    float x, y;

    Vector2 operator-(const Vector2& v);
    Vector2 operator+(const Vector2& v);
    Vector2 operator*(float A);
    Vector2 operator/(float A);
    void operator+=(const Vector2& v);
    void operator*=(float A);
    bool Not_Zero();
};

Vector2 operator*(float A, Vector2&& v);
void Print_Vector2(const Vector2& v);

#endif //Vector2_hpp
