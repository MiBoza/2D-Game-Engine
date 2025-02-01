#include "RigidBody.hpp"

RigidBody::RigidBody(const Uint32& p_delta_time, const TextureManager* p_texture_manager):
    delta_time(p_delta_time),
    Object(p_texture_manager){
    flags |= RIGID;
}

void RigidBody::Rigid_Update(){
    outdated = 1;
    pos += velocity*delta_time;
    if(Not_Zero(acceleration)){
        Vector2 tempy = acceleration*delta_time;
        pos += tempy*delta_time/2;
        velocity += tempy;
    }
}

void RigidBody::Collide(const Line& line){
    const Vector2& a = acceleration;
    Vector2& v1 = velocity;
    Vector2 p1 = Get_Pos();
    const float& h = line.h;
    const float& k = line.k;
    const float& l = line.l;

    //0 = e(dt)^2 + f(dt) + g
    float e = (a.x*k - a.y*h)/2;
    float f = v1.y*h - v1.x*k;
    float g = p1.x*k - p1.y*h + l;

    //Find how long ago the collision ocurred
    float dt;

    if(e == 0)
        dt = -g/f;
    else{
        float determinant = f*f - 4*e*g;
        if(determinant < 0){
            printf("determinant = %f\n", determinant);
            exit(1);
        }
        float sqrt_determinant = sqrt(determinant);
        dt = (-f - sqrt_determinant)/2/e;
        if(dt < 0 || dt > delta_time)
            dt = (-f + sqrt_determinant)/2/e;
    }

    //At collision
    Vector2 p0 = 0.5*a*dt*dt - v1*dt + p1;
    Vector2 v0 = v1 - a*dt;

    //Outwardly perpendicular direction to the line
    Vector2 dp = {k, -h};

    //Projection of v0 on dp
    Vector2 vp = (v0 * dp) * dp/Magnitude_Squared(dp);

    //Collision inverts component vp of velocity
    v0 += -2*vp;

    //Calculating position after collision
    p1 = 0.5*a*dt*dt + v0*dt + p0;
    v1 = v0 + a*dt; //Update velocity

    //Write results;
    Set_Pos(p1);
}
