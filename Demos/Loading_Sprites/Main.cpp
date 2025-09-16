#include "Silly_Core.hpp"

class Game : public Silly_Core{
    using Silly_Core::Silly_Core;

    Atlas* a_square;
    Atlas* a_3D;
    Vector2 size = {200, 200};

    Object *square;
    Object *cube;
    Object *cone;
    Object *cylinder;

    Object* Init_Object(Atlas* atlas, int row, int column);
public:
    void SetUp();
    void Update();
};

Object* Game::Init_Object(Atlas* atlas, int row, int column){
    Object* obj;

    obj = AddObject();
    atlas->Assign_Sprite(obj, row, column);
    obj->Set_Size(size);

    return obj;
}

void Game::SetUp(){
    input = new Default_Input(state);
    a_square = texture_manager->Load("Assets/Square.png");
    a_3D = texture_manager->Load("Assets/Atlas.png", 2, 5);

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

void Game::Update(){}

int main(){
    Game* game = new Game("Load Sprites");
    game->SetUp();

    while(game->state){
        game->input->Input_Update();
        game->Components();
    }

    delete game;

    return 0;
}
