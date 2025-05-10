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

void Vector2::Normalise(){
    float magnitude = Magnitude(*this);
    if(magnitude == 0)
        return;

    x /= magnitude;
    y /= magnitude;
}

float Magnitude_Squared(const Vector2& u){
    return Ipow(u.x, 2) + Ipow(u.y, 2);
}

float Magnitude(const Vector2& u){
    return sqrt( Magnitude_Squared(u) );
}

float Angle(const Vector2& u){
    #define Tau 2*M_PI
    if(u.x < 0){
        Vector2 temp({-u.x, -u.y});
        return fmod(Tau + Angle(temp), Tau) - M_PI;
    }
    if(u.x < 1e-5)
        return u.y > 0 ? M_PI_2 : -M_PI_2;

    return atan(u.y/u.x);
}

float Angle_Degrees(const Vector2& u){
    return 180*Angle(u)/M_PI;
}

Vector2 Polar_Constructor(float magnitude, float angle){
    // Vector2 u( { magnitude*cos(angle), magnitude*sin(angle) } );
    Vector2 u;
    u.x = magnitude*cos(angle);
    u.y = magnitude*sin(angle);

    return u;
}

Vector2 Degree_Constructor(float magnitude, float degrees){
    float angle = degrees*M_PI/180;
    return Polar_Constructor(magnitude, angle);
}

Vector2 operator-(const Vector2& u, const Vector2& v){
    Vector2 result = {u.x - v.x, u.y - v.y};
    return result;
}

Vector2 operator+(const Vector2& u, const Vector2& v){
    Vector2 result = {u.x + v.x, u.y + v.y};
    return result;
}

float operator*(const Vector2& u, const Vector2& v){
    float result = u.x*v.x + u.y*v.y;
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

bool Is_Zero(const Vector2& u){
    if(u.x || u.y)
        return 0;
    else
        return 1;
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

void Print_Vector2(const char* string, const Vector2& u){
    printf("%s[%.2f, %.2f]\n", string, u.x, u.y);
}
