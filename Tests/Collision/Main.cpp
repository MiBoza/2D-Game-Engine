#include "Aggregate.hpp"
// #include <stdio.h>

class Game : public Aggregate{
    using Aggregate::Aggregate;
    Vector2 size = {40, 40};
    Line lines[4];

    Atlas* atlas;
    RigidBody* square;
public:
    void SetUp();
    void Update();
};

void Game::SetUp(){
    atlas = texture_manager->Load("Assets/Atlas.png", 2, 5);

    // circle = AddRigidBody();
    // circle->Set_Texture(circle_sprite_id);
    // circle->Set_Pos({450, 300});
    // circle->Set_Size(size);
    // circle->velocity = {0.95, -0.275};
    // circle->acceleration = {-0.001, 0.006};

    // AddEvent(10000, 2999, ByeBye_Circle);
    // AddEvent(11500, 1999, End_Game);

    square = AddRigidBody();
    atlas->Assign_Sprite(square->object, 6);
    square->Set_Pos({161, 150});
    square->Set_Size(size);
    square->velocity = {0.6, 0.5};
    square->acceleration = {0.0001, 0.003};

    // Object* square2 = AddObject();
    // square2->Set_Texture(square_index);
    // square2->Set_Pos({739, 550});
    // square2->Set_Size(size);
    //
    // Object* square3 = AddObject();
    // square3->Set_Texture(square_index);
    // square3->Set_Pos({450, 50});
    // square3->Set_Size(size);

    Set_Framerate(30);
    // Timelimit_Event(10200);
    Timelimit_Thread(4200);

    Vector2 mid_size(size/2);
    Vector2 mid_corner = window_res - mid_size;

    // hy = kx + l
    lines[0] = { 0,  1, -mid_size.x};     // left
    lines[1] = { 0, -1,  mid_corner.x};   // right
    lines[2] = {-1,  0, -mid_size.y};     // up
    lines[3] = { 1,  0,  mid_corner.y};   // bottom
}

void Game::Update(){
    // if(circle)
    //     Collision(circle);
    if(square){
        for(const Line& line : lines)
            square->Collide(line);
    }
    // if(square2)
    //     Collision(square2);
}

int main(){
    Game* game = new Game("Mystery Title");
    game->SetUp();

    while(game->running){
        game->input.Input_Update();
        game->Timing();
        // game->Event_Handler();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
