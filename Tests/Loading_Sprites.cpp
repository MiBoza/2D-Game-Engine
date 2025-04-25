#include "Aggregate.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    Atlas* a_square;
    Atlas* a_3D;
    Vector2 texture_res = {787, 787};
    Vector2 size = {200, 200};

    Object *square;
    Object *cube;
    Object *cone;
    Object *cylinder;

    Object* Init_Object(Atlas* atlas, int row, int column);
public:
    void SetUp();
};

Object* Game::Init_Object(Atlas* atlas, int row, int column){
    Object* obj;

    obj = AddObject();
    atlas->Assign_Sprite(obj, row, column);
    obj->Set_Size(size);

    return obj;
}

void Game::SetUp(){
    a_square = texture_manager->Load("assets/Square.png", texture_res);
    a_3D = texture_manager->Load("assets/3D.png", texture_res, 1, 3);

    //Loading a single sprite
    square = AddObject();
    a_square->Assign_Sprite(square);
    square->Set_Size({50, 50});
    square->Set_Pos({25, 25});

    //Loading multiple sprites from atlas
    cube = Init_Object(a_3D, 0, 0);
    cylinder = Init_Object(a_3D, 0, 1);
    cone = Init_Object(a_3D, 0, 2);

    cube->Set_Pos({623, 470});
    cylinder->Set_Pos({450, 170});
    cone->Set_Pos({277, 470});
}

int main(){
    Game* game = new Game("Load Sprites");
    game->SetUp();

    while(game->running){
        game->Input_Handler();
        game->Components();
    }

    delete game;

    return 0;
}
