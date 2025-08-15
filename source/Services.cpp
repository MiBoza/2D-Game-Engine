#ifnder Services_hpp
#define Services_hpp

#include "Aggregate.hpp"

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
        if(object->flags & OUTDATED)
            object->Update_Dest();
        if(object->flags & IMAGE)
            Render(object, object->image);
        if(object->flags & TEXT)
            Render(object, object->text);
        if(object->flags & BEHAVIOUR)
            object->behaviour.execute();
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
    obj->flags |= OUTDATED;
    SDL_QueryTexture(text.texture, NULL, NULL, &text.source.w, &text.source.h);
    SDL_FreeSurface(Surface);
}

#endif	// Services_hpp
