#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    int circle_sprite_id;
    int square_sprite_id;
    Vector2 size = {20, 20};
    Vector2 texture_res = {787, 787};

    Object *circle1, *circle2, *circle3;
    Object *square1, *square2, *square3;

    Object* Init_Object(int sprite_id);
public:
    void SetUp();
    void Update();
};

Object* Game::Init_Object(int sprite_id){
    Object* obj;

    obj = AddObject();
    obj->Set_Texture(sprite_id);
    obj->Set_Size(size);

    return obj;
}

void Game::SetUp(){
    circle_sprite_id = texture_manager->Load("assets/Circle.png", texture_res);
    square_sprite_id = texture_manager->Load("assets/Square.png", texture_res);

    circle1 = Init_Object(circle_sprite_id);
    circle2 = Init_Object(circle_sprite_id);
    circle3 = Init_Object(circle_sprite_id);
    square1 = Init_Object(square_sprite_id);
    square2 = Init_Object(square_sprite_id);
    square3 = Init_Object(square_sprite_id);

    Set_Framerate(40);
}

Vector2 Swirl(float degrees){
    float angle = degrees*M_PI/180;

    Vector2 pos;

    pos.x = 450-400*cos(angle);
    pos.y = 300-100*sin(2*angle);

    return pos;
}

void Game::Update(){
    const static float frequency = 0.12;

    circle1->Set_Pos( Swirl(frequency*runtime +   0) );
    circle2->Set_Pos( Swirl(frequency*runtime +  24) );
    square1->Set_Pos( Swirl(frequency*runtime +  48) );
    square2->Set_Pos( Swirl(frequency*runtime +  72) );
    square3->Set_Pos( Swirl(frequency*runtime +  96) );
    circle3->Set_Pos( Swirl(frequency*runtime + 120) );
}

int main(){
    Game* game = new Game("Infinity Swirl");
    game->SetUp();

    while(game->running){
        game->Input_Handler();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
