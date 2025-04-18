#include "Aggregate.hpp"

class Actor;

class Game : public Aggregate{
    using Aggregate::Aggregate;

    int circle_sprite_id;
    int square_sprite_id;
    Vector2 size = {20, 20};

    Actor* all_actors[6];

    Actor* Initialise_Actor(Object* p_obj, float degrees, int sprite_id);
public:
    void SetUp();
    void Update();
    ~Game(){
        for(Actor* i : all_actors)
        delete i;
        // Aggregate::~Aggregate();
    }
};

class Actor{
public:
    Object* object;
    float angle;

    Actor(Object* p_obj, float degrees):
        object(p_obj), angle(degrees*M_PI/180){}
    void Put_In_Place(){
        Vector2 pos;

        pos.x = 450-400*cos(angle);
        pos.y = 300-100*sin(2*angle);

        // Print_Vector2("pos = ", pos);

        object->Set_Pos(pos);
    }
    void Swirl(const Uint32& delta_time){
        const static float speed = 2;
        angle += 2*delta_time;
        Put_In_Place();
    }
};

Actor* Game::Initialise_Actor(Object* obj, float degrees, int sprite_id){
    Actor* act = new Actor(obj, degrees);
    obj = AddObject();
    obj->Set_Texture(sprite_id);
    obj->Set_Size(size);
    act->Put_In_Place();

    return act;
}

void Game::SetUp(){
    Vector2 texture_res({787, 787});
    circle_sprite_id = texture_manager->Load("assets/Circle.png", texture_res);
    square_sprite_id = texture_manager->Load("assets/Square.png", texture_res);

    Object *circle1, *circle2, *circle3, *square1, *square2, *square3;

    all_actors[0] = Initialise_Actor(circle1, 0,   circle_sprite_id);
    all_actors[1] = Initialise_Actor(circle2, 60,  circle_sprite_id);
    all_actors[2] = Initialise_Actor(circle3, 120, circle_sprite_id);
    all_actors[3] = Initialise_Actor(square1, 180, square_sprite_id);
    all_actors[4] = Initialise_Actor(square2, 240, square_sprite_id);
    all_actors[5] = Initialise_Actor(square3, 300, square_sprite_id);

    Set_Framerate(14);
}

void Game::Update(){
    for(Actor* i : all_actors)
        i->Swirl(delta_time);
}

int main(){
    Game* game = new Game("Infinity Swirl");
    game->SetUp();

    while(game->running){
        game->Input_Handler();
        // game->Event_Handler();
        game->Timing();
        // game->Update();
        game->Components();
    }

    delete game;

    return 0;
}
