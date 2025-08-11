#include "Aggregate.hpp"
#include <filesystem>
using std::list;

Aggregate::Aggregate(const char* title, bool fullscreen){
    int flags = 0;
    Vector2& window_res = Aggregate::window_res;

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
        window_res.x = 1920;
        window_res.y = 1080;
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        puts("SDL video couldn't initialise.");
        puts( SDL_GetError() );
        exit(1);
    }
    if(!IMG_Init(IMG_INIT_PNG)){
        puts("SDL_Image couldn't initialise.");
        puts( SDL_GetError() );
        exit(1);
    }
    if(TTF_Init() == -1){
        puts("SDL_ttf couldn't initialise.");
        puts( SDL_GetError() );
        exit(1);
    }
    int pos_x, pos_y;
    pos_x = pos_y = SDL_WINDOWPOS_CENTERED;
    window = SDL_CreateWindow(title, pos_x, pos_y, window_res.x, window_res.y, flags);
    if(!window){
        puts("Window couldn't open correctly");
        puts( SDL_GetError() );
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        puts("Renderer didn't initialise");
        puts( SDL_GetError() );
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Red, Green, Blue, Something
    running = 1;

    texture_manager = new TextureManager(renderer, window_res);
}

void Aggregate::Destroy_Object(Object* obj){
    if(obj->rb)
        delete obj->rb;
    delete obj;
}

void Aggregate::Components(){
    //Looks through the list of objects and
    //Renders or calculates physics as required

    SDL_RenderClear(renderer);
    typename std::list<Object*>::iterator it = objects.begin();
    for(; it != objects.end();){
        Object* object = *it;

        if(object->flags & DELETED){
            Destroy_Object(object);
            it = objects.erase(it);
            continue;
        }
        ++it;
        if(object->outdated)
            object->Update_Dest();
        if(object->flags & IMAGE)
            Render(object, object->image);
        if(object->flags & TEXT)
            Render(object, object->text);
        if(object->rb){
            RigidBody* rb = object->rb;
            rb->Rigid_Update();
        }
    }
    SDL_RenderPresent(renderer);
}

void Aggregate::Render(const Object* obj, const Texture_Wrapper& tx_wrap){
    if(obj->flags & COPYEX)
        SDL_RenderCopyEx(renderer, tx_wrap.texture, &tx_wrap.source, &tx_wrap.destination,
            obj->rotation_angle, NULL, obj->flip);
    else
        SDL_RenderCopy(renderer, tx_wrap.texture, &tx_wrap.source, &tx_wrap.destination);
}

Object* Aggregate::AddObject(RigidBody* p_rb){
    Object* object = new Object(p_rb);
    object->pos = window_res/2;
    objects.push_back(object);
    return object;
}

Object* Aggregate::AddEXObject(RigidBody* p_rb){
    Object* object = AddObject(p_rb);
    object->flags |= COPYEX;
    return object;
}

Object* Aggregate::AddTextBox(const char line[]){
    Object* object = AddObject();
    object->flags |= TEXT;
    Set_Text(object, line);

    return object;
}

void Aggregate::Set_Text(Object* obj, const char line[]){
    if(!(obj->flags & TEXT)){
        puts("Warning. Trying to set text to object without TEXT flag");
        return;
    }
    Texture_Wrapper& text = obj->text;
    if(text.texture)
        SDL_DestroyTexture(text.texture);

    obj->colour = {0x00, 0x00, 0x00, 0xFF};
    text.source.x = 0;
    text.source.y = 0;
    SDL_Surface* Surface = TTF_RenderText_Blended(texture_manager->font, line, obj->colour);
    text.texture = SDL_CreateTextureFromSurface(renderer, Surface);
    if(!text.texture){
        puts("Error. Text failed to render");
        puts( SDL_GetError() );
        exit(1);
    }
    obj->outdated = 1;
    SDL_QueryTexture(text.texture, NULL, NULL, &text.source.w, &text.source.h);
    SDL_FreeSurface(Surface);
}


RigidBody* Aggregate::AddRigidBody(Object* object){
    RigidBody* rb = new RigidBody(delta_time, object);
    if(!rb->object)
        rb->object = AddObject(rb);
    return rb;
}

Aggregate::~Aggregate(){
    delete texture_manager;
    texture_manager = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for(Object* obj : objects){
        Destroy_Object(obj);
    }
    for(Event* e : events){
        delete e;
    }

    if(relaxation > runtime)
        relaxation = runtime;

    printf("Game ended after %i ms.\n", runtime);
    printf("Relaxed for %i ms (%.2f", relaxation, 100.0*relaxation/runtime);
    puts("%).");
    SDL_Quit();
}
