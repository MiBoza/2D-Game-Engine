#include "Aggregate.hpp"
#include "Input_Handler.hpp"

class Game : public Aggregate{
    using Aggregate::Aggregate;

    RigidBody* player;
    Atlas* circle;
    Input_Handler* my_input;

    RigidBody* Init_Rb(Atlas* atlas, const Vector2& size);
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
    input = new Input_Handler(state);
    my_input = reinterpret_cast<Input_Handler*>(input);
    circle = texture_manager->Load("Assets/Circle.png");
    Vector2 size({20, 20});

    player = Init_Rb(circle, size);
    Set_Framerate(30);
}

void Game::Update(){
    // Player Movement
    Vector2 v({0, 0});
    static const float turn_speed = 0.15;
    static const float p_speed = 0.5;
    static const float a = 1-turn_speed;
    static const float b = turn_speed*p_speed;

    if(my_input->up_k)
        v += { 0, -1};
    if(my_input->down_k)
        v += { 0,  1};
    if(my_input->right_k)
        v += { 1,  0};
    if(my_input->left_k)
        v += {-1,  0};

    if(Is_Zero(v))
        player->velocity = v;
    else{
        v.Normalise();
        player->velocity *= a;
        player->velocity += b*v;
    }
}

int main(){
    Game* game = new Game("Player Movement");
    game->SetUp();

    while(game->state){
        game->input->Input_Update();
        game->Timing();
        game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
