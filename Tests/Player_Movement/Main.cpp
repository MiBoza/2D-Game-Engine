#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    RigidBody* player;
    Atlas* circle;

    RigidBody* Init_Rb(Atlas* atlas, const Vector2& size);
    void Player_Movement();
public:
    void SetUp();
    void Update();
};

RigidBody* Game::Init_Rb(Atlas* atlas, const Vector2& size){
    RigidBody* rb;
    rb = AddRigidBody();

    Object* obj = rb->object;
    atlas->Assign_Sprite(obj);
    obj->Set_Size(size);

    return rb;
}

void Game::SetUp(){
    circle = texture_manager->Load("Assets/Circle.png");
    Vector2 size({20, 20});

    player = Init_Rb(circle, size);
    // player->velocity = {0.1, 0.01};
    Set_Framerate(30);
}

void Game::Player_Movement(){
    Vector2 v({0, 0});
    static const float turn_speed = 0.15;
    static const float p_speed = 0.3;
    static const float a = 1-turn_speed;
    static const float b = turn_speed*p_speed;

    if(input.up_k)
        v += { 0, -1};
    if(input.down_k)
        v += { 0,  1};
    if(input.right_k)
        v += { 1,  0};
    if(input.left_k)
        v += {-1,  0};

    if(Is_Zero(v))
        player->velocity = v;
    else{
        v.Normalise();
        player->velocity *= a;
        player->velocity += b*v;
    }
}

void Game::Update(){
    Player_Movement();
}

int main(){
    Game* game = new Game("Player Movement");
    game->SetUp();

    while(game->running){
        game->input.Input_Update();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
