#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    Atlas* a_arrow;
    Atlas* a_circle;
    Atlas* a_square;
    Vector2 texture_res = {787, 787};
    Vector2 arrow_pos = {450, 80};

    Object *arrow, *circle;
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
    a_arrow = texture_manager->Load("assets/Arrow.png", {787, 345});
    a_circle = texture_manager->Load("assets/Circle.png", texture_res);
    a_square = texture_manager->Load("assets/Square.png", texture_res);

    Vector2 arrow_size({150, 50});
    Vector2 other_size({20, 20});

    arrow = Init_Object(a_arrow, arrow_size);
    circle = Init_Object(a_circle, other_size);
    square1 = Init_Object(a_square, other_size);
    square2 = Init_Object(a_square, other_size);
    square3 = Init_Object(a_square, other_size);
    square4 = Init_Object(a_square, other_size);
    square5 = Init_Object(a_square, other_size);

    arrow->Set_Pos(arrow_pos);

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

    square1->Set_Pos( Swirl(frequency*runtime +   0) );
    square2->Set_Pos( Swirl(frequency*runtime +  24) );
    square3->Set_Pos( Swirl(frequency*runtime +  48) );
    square4->Set_Pos( Swirl(frequency*runtime +  72) );
    square5->Set_Pos( Swirl(frequency*runtime +  96) );
    circle->Set_Pos( Swirl(frequency*runtime + 120) );     //Lead

    Vector2 lead_pos = circle->Get_Pos();
    float degrees = Angle_Degrees(lead_pos-arrow_pos);

    arrow->Rotate(degrees);
    // arrow->Flip_Horizontally();
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
