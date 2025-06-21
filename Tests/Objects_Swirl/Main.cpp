#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    Atlas* a_circle;
    Atlas* a_square;

    Object *circle;
    Object *square1, *square2, *square3, *square4, *square5;

    Object* Init_Object(Atlas* atlas, const Vector2& size);
public:
    void SetUp();
    void Update();
};

Object* Game::Init_Object(Atlas* atlas, const Vector2& size){
    Object* obj;

    obj = AddObject();
    atlas->Assign_Sprite(obj);
    obj->Set_Size(size);

    return obj;
}

void Game::SetUp(){
    a_circle = texture_manager->Load("Assets/Circle.png");
    a_square = texture_manager->Load("Assets/Square.png");

    Vector2 size({20, 20});

    circle = Init_Object(a_circle, size);
    square1 = Init_Object(a_square, size);
    square2 = Init_Object(a_square, size);
    square3 = Init_Object(a_square, size);
    square4 = Init_Object(a_square, size);
    square5 = Init_Object(a_square, size);

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

    square1->Set_Pos( Swirl(frequency*runtime +  0) );
    square2->Set_Pos( Swirl(frequency*runtime + 24) );
    square3->Set_Pos( Swirl(frequency*runtime + 48) );
    square4->Set_Pos( Swirl(frequency*runtime + 72) );
    square5->Set_Pos( Swirl(frequency*runtime + 96) );
    circle->Set_Pos( Swirl(frequency*runtime + 120) );     //Lead
}

int main(){
    Game* game = new Game("Infinity Swirl");
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
