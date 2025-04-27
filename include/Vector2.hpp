#ifndef Vector2_hpp
#define Vector2_hpp

#include <stdio.h>
#include <cmath>

float Ipow(float x, int y);

struct Vector2{
    float x, y;
};

float Magnitude_Squared(const Vector2& u);
float Magnitude(const Vector2& u);
float Angle(const Vector2& u);
float Angle_Degrees(const Vector2& u);
Vector2 Polar_Constructor(float magnitude, float angle);
Vector2 Degree_Constructor(float magnitude, float degrees);
Vector2 operator-(const Vector2& u, const Vector2& v);
Vector2 operator+(const Vector2& u, const Vector2& v);
float operator*(const Vector2& u, const Vector2& v);
Vector2 operator*(const Vector2& u, float A);
Vector2 operator/(const Vector2& u, float A);
bool Not_Zero(const Vector2& u);
bool Is_Zero(const Vector2& u);
void operator+=(Vector2& u, const Vector2& v);
void operator*=(Vector2& u, float A);
Vector2 operator*(const Vector2& u, float A);
Vector2 operator*(float A, const Vector2& u);
void Print_Vector2(const char* string, const Vector2& u);

#endif //Vector2_hpp
